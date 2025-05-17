/*
 * @Author: mtz nuaamzt@nuaa.edu.cn
 * @Date: 2025-05-18 01:45:27
 * @LastEditors: mtz nuaamzt@nuaa.edu.cn
 * @LastEditTime: 2025-05-18 01:53:14
 * @FilePath: /g4_proton/include/B1EventAction.hh
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */


#ifndef EventAction_h
#define EventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"
#include "RunAction.hh"



class EventAction : public G4UserEventAction
{
  public:
    EventAction(RunAction* runAction);
    virtual ~EventAction();

    virtual void BeginOfEventAction(const G4Event* event);
    virtual void EndOfEventAction(const G4Event* event);

    void AddCounts(G4int counts) { fCounts += counts; }

    

  private:
    RunAction* fRunAction;
    G4double fCounts;
    
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

    
