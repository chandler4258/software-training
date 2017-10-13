#include <iostream>
#include <STSL/RJRobot.h>
#include <vector>
#include <algorithm>

using namespace std;

int main() {

    RJRobot robot;

    vector<int> measurements;

    int black_threshold = 100;

    int gray_threshold = 85;

    while(measurements.empty() || measurements.back() > black_threshold) {
        measurements.push_back(robot.LightValue());

        robot.SetMotor(MotorPort::A, 100);
        robot.SetMotor(MotorPort::B, 100);
        robot.Wait(250ms);

    }

    cout << measurements.back() << endl;

    robot.StopMotors();

    measurements.erase(measurements.end() - 1);

    auto is_gray = bind2nd(less<int>(), gray_threshold);

    int number_gray = count_if(measurements.begin(), measurements.end(), is_gray);

    cout << number_gray << " grey squares found" << endl;

    return 0;
}