#include "WiFiSimulator.h"

void simulateWiFi5(int userCount) {
    WiFi5AP ap;
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
    std::cout << "WiFi 5 Simulation Results:\n";
    for (int userCount : {1, 10, 100}) {
        simulateWiFi5(userCount);
    }
    return 0;
}
