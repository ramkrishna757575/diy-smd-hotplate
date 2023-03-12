#pragma once

typedef struct
{
    String name;
    String meta;

    int soak;
    int reflow;
    int peak;

    int heatup_time;
    int soak_time;
    int rampup_time;
    int peak_time;
    int rampdn_time;

} ReflowProfile;

#define numProfile 2

ReflowProfile profile[numProfile];

void getProfiles() {
    profile[0] = (ReflowProfile){
        "Relife Rl-405", "Sn42/Bi58  | 138Deg", 100, 138, 165, 90, 90, 30, 30, 90};
    profile[1] = (ReflowProfile){
        "Mechanic XG50", "Tin63/Pb37 | 183Deg", 150, 183, 220, 90, 120, 40, 20, 120};
}
