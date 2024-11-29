#include "WiFiSimulator.h"

void simulateWiFi6(int userCount) {
    WiFi6AP ap;
    std::vector<User> users;
    for (int i = 0; i < userCount; ++i) {
        users.emplace_back(i);
    }

    for (auto& user : users) {
        ap.transmit(user);
    }

    std::cout << "Results for " << userCount << " users:\n";
    ap.computeMetrics();
}

int main() {
    std::cout << "WiFi 6 Simulation Results:\n";
    for (int userCount : {1, 10, 100}) {
        simulateWiFi6(userCount);
    }
    return 0;
}
