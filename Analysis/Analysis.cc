/*
 * @Author: mtz nuaamzt@nuaa.edu.cn
 * @Date: 2025-05-18 16:12:06
 * @LastEditors: mtz nuaamzt@nuaa.edu.cn
 * @LastEditTime: 2025-05-18 16:55:13
 * @FilePath: /g4_proton/Analysis/Analysis.cc
 * @Description: 使用ROOT文件保存数据，文件路径为rt/output_target{i}.root.
 tree中含有Beam,Energy,Counts,一个root文件Beam,Energy的个数与线程数对应，应该每个数都相同，代表束流强度和能量；Counts应当累加起来才能得到F18产额
 写一个脚本将束流、能量和产额保存到一个变量下
 对于能量不是单值的情况，取平均值
 */

#include "TCanvas.h"
#include "TFile.h"
#include "TGraph.h"
#include "TH2.h"
#include "TH2D.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TTree.h"
#include "iostream"
#include "vector"
#include <string>
#include <unistd.h>

void Analysis() {
  TCanvas *tc = new TCanvas("tc", "tc", 800, 600);
  // 获取rt/下的所有root文件路径
  std::vector<std::string> rootFiles;
  std::string path = "./rt/";
  std::string fileName = "output_target";
  std::string fileType = ".root";
  for (int i = 0; i < 100; i++) {
    std::string filePath = path + fileName + std::to_string(i) + fileType;
    // 存在性检查
    if (access(filePath.c_str(), F_OK) == -1) {
      // std::cout << "File does not exist: " << filePath << std::endl;
      continue;
    }
    rootFiles.push_back(filePath);
  }
  // 输出文件路径
  for (const auto &filePath : rootFiles) {
    std::cout << filePath << std::endl;
  }

  // 一个root获取三个数字
  // 创建变量保存这三个数字
  std::vector<std::vector<double>> data; // 不要指定大小
  // 读取root文件
  for (const auto &filePath : rootFiles) {
    TFile *file = new TFile(filePath.c_str());
    if (!file || file->IsZombie()) {
      std::cout << "Error opening file: " << filePath << std::endl;
      continue;
    }
    // 获取树
    TTree *tree = (TTree *)file->Get("tree");
    if (!tree) {
      std::cout << "Error getting tree from file: " << filePath << std::endl;
      continue;
    }
    // 读取数据
    int counts;
    double energy;
    int beam; // 修改为int类型
    tree->SetBranchAddress("Counts", &counts);
    tree->SetBranchAddress("Energy", &energy);
    tree->SetBranchAddress("Beam", &beam);

    double totalCounts = 0;
    double totalEnergy = 0;
    double totalBeam = 0;
    // 遍历树
    for (int i = 0; i < tree->GetEntries(); i++) {
      tree->GetEntry(i);
      // 计数累加，能量和束流强度取中间值
      totalCounts += counts;
      totalEnergy += energy;
      totalBeam += beam;
      // std::cout << "Counts: " << counts << ", Energy: " << energy << ", Beam:
      // " << beam << std::endl;
    }
    // 计算平均值
    double averageEnergy = totalEnergy / tree->GetEntries();
    double averageBeam = totalBeam / tree->GetEntries();
    // 结果放进三维数组
    data.push_back({averageEnergy, averageBeam, totalCounts});
    // 关闭文件
    file->Close();
  }

  // 画图
  // 产额随能量变化
  // 产额随强度变化
  // 能量-强度关联（Dalitz）
  TGraph *graph_N_E = new TGraph();
  // 单独从data中取出能量和产额数据，填充到graph中
  for (size_t i = 0; i < data.size(); i++) {
    graph_N_E->SetPoint(i, data[i][0], data[i][2]);
    std::cout << "Energy: " << data[i][0] << ", Counts: " << data[i][2]
              << std::endl;
  }
  graph_N_E->SetTitle("Counts vs Energy");
  graph_N_E->GetXaxis()->SetTitle("Energy (MeV)");
  graph_N_E->GetYaxis()->SetTitle("Counts");
  graph_N_E->Draw("AP");
  // 数据点大小自动优化
  graph_N_E->SetMarkerStyle(20);
  graph_N_E->SetMarkerSize(1.5);
  graph_N_E->SetMarkerColor(kBlue);
  // 保存图像
  tc->SaveAs("Counts_vs_Energy.pdf");
  TGraph *graph_N_B = new TGraph();
  // 单独从data中取出强度和产额数据，填充到graph中
  for (size_t i = 0; i < data.size(); i++) {
    graph_N_B->SetPoint(i, data[i][1], data[i][2]);
    std::cout << "Beam: " << data[i][1] << ", Counts: " << data[i][2]
              << std::endl;
  }
  graph_N_B->SetTitle("Counts vs Beam");
  graph_N_B->GetXaxis()->SetTitle("Beam (MeV)");
  graph_N_B->GetYaxis()->SetTitle("Counts");
  graph_N_B->Draw("AP");
  // 数据点大小自动优化
  graph_N_B->SetMarkerStyle(20);
  graph_N_B->SetMarkerSize(1.5);
  graph_N_B->SetMarkerColor(kRed);
  // 保存图像
  tc->SaveAs("Counts_vs_Beam.pdf");

  // 计算能量和强度的最大最小值
  double minE = 1e9, maxE = -1e9, minB = 1e9, maxB = -1e9;
  for (const auto &row : data) {
    if (row[0] < minE)
      minE = row[0];
    if (row[0] > maxE)
      maxE = row[0];
    if (row[1] < minB)
      minB = row[1];
    if (row[1] > maxB)
      maxB = row[1];
  }

  // 给范围留一点边界
  double marginE = (maxE - minE) * 0.05;
  double marginB = (maxB - minB) * 0.05;

  // 创建TH2D直方图，范围自动
  TH2D *h2 = new TH2D("h2", "Counts vs Energy and Beam", 100, minE - marginE,
                      maxE + marginE, 100, minB - marginB, maxB + marginB);

  // 填充数据
  for (size_t i = 0; i < data.size(); i++) {
    h2->Fill(data[i][0], data[i][1], data[i][2]);
  }
  h2->GetXaxis()->SetTitle("Energy (MeV)");
  h2->GetYaxis()->SetTitle("Beam (MeV)");
  h2->GetZaxis()->SetTitle("Counts");
  h2->SetTitle("Counts vs Energy and Beam");

  // 设置统计框位置（右上角，轴外）
  // 关闭统计框
  h2->SetStats(0);

  h2->Draw("COLZ");
  // 保存图像
  tc->SaveAs("Counts_vs_Energy_and_Beam.pdf");
}