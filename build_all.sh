sudo rm -rf ~/ProjectRinzler/Drivers/compass/build
sudo rm -rf ~/ProjectRinzler/Drivers/svp/build
sudo rm -rf ~/ProjectRinzler/Drivers/motor/build
sudo rm -rf ~/ProjectRinzler/Drivers/adc/build
sudo rm -rf ~/ProjectRinzler/Drivers/sonar/build
sudo rm -rf ~/ProjectRinzler/Drivers/fwdcam/build
sudo rm -rf ~/ProjectRinzler/Soft_Nodes/control/build
sudo rm -rf ~/ProjectRinzler/Soft_Nodes/depthMod/build
sudo rm -rf ~/ProjectRinzler/Soft_Nodes/logger/build
sudo rm -rf ~/ProjectRinzler/Soft_Nodes/pidRamp/build
sudo rm -rf ~/ProjectRinzler/Soft_Nodes/sonarLoc/build
sudo rm -rf ~/ProjectRinzler/Soft_Nodes/spammer/build
sudo rm -rf ~/ProjectRinzler/High_Level_Nodes/missionPlanner/build
sudo rm -rf ~/ProjectRinzler/High_Level_Nodes/pilot/build

rosmake -a
