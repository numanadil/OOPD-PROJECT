#include "WiFiSimulator.h"

// Packet Implementation
Packet::Packet(int size) 
    : size(size), transmissionTime(size * 8 / (BANDWIDTH * MODULATION_RATE * CODING_RATE)) {}

// User Implementation
User::User(int id) : id(id) {}

int User::getId() const {
    return id;
}

// AccessPoint Base Class Implementation
AccessPoint::AccessPoint() : throughput(0), avgLatency(0), maxLatency(0) {}

void AccessPoint::computeMetrics() {
    if (latencies.empty()) return;
    maxLatency = *std::max_element(latencies.begin(), latencies.end());
    avgLatency = std::accumulate(latencies.begin(), latencies.end(), 0.0) / latencies.size();
    std::cout << "Throughput: " << throughput << " Mbps\n";
    std::cout << "Average Latency: " << avgLatency * 1000 << " ms\n"; // Convert to ms
    std::cout << "Maximum Latency: " << maxLatency * 1000 << " ms\n"; // Convert to ms
}

// WiFi4AP Implementation
WiFi4AP::WiFi4AP() : AccessPoint() {}

void WiFi4AP::transmit(User& user) {
    // Define a random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, 1);  // to generate a random value between 0 and 1
    
    // Stronger contention penalty: non-linear decrease in throughput
    double contentionPenalty = 1.0 / (1 + 0.5 * user.getId() * log(user.getId() + 1)); // Exponential scaling penalty

    // Create a packet with the defined size
    Packet packet(PACKET_SIZE);

    // Latency factors to simulate growing latency as more users are added
    double latencyFactor = 0.001 + 0.01 * user.getId(); // Increases latency as the number of users grows
    double effectiveLatency = packet.transmissionTime + latencyFactor;  // Add extra delay based on user count

    // Define packet loss probability based on the number of users
    double packetLossProbability = 0.0;
    if (user.getId() > 1 && user.getId() <= 10) {
        packetLossProbability = 0.1;  // 10% packet loss for 2-10 users
    } else if (user.getId() > 10 && user.getId() <= 100) {
        packetLossProbability = 0.25;  // 25% packet loss for 11-100 users
    }

    // Simulate packet loss with random chance
    if (dis(gen) < packetLossProbability) {
        std::cout << "Packet lost for user " << user.getId() << std::endl;
        // Skip adding this packet's latency and throughput if it's lost
        return;
    }

    // Add the transmission latency (if no packet loss)
    latencies.push_back(effectiveLatency);

    // Add the throughput (penalized by contention and packet loss)
    throughput += contentionPenalty * (packet.size * 8) / (effectiveLatency * 1e6); // Mbps

    // Simulate retransmission if packet loss occurs
    if (dis(gen) < packetLossProbability) {
        double retransmissionDelay = 0.005; // 5ms for retransmission
        latencies.push_back(retransmissionDelay);  // Add retransmission delay to latencies
        throughput -= 0.5 * (packet.size * 8) / (retransmissionDelay * 1e6); // Reduce throughput due to retransmission
    }
}




// WiFi5AP Implementation
WiFi5AP::WiFi5AP() : AccessPoint() {}

void WiFi5AP::transmit(User& user) {
    // Increasing throughput with more users (MU-MIMO efficiency)
    double efficiencyFactor = 1 + 0.05 * user.getId();
    Packet csiPacket(200); // CSI packet size is 200 bytes
    Packet dataPacket(PACKET_SIZE);

    // CSI Transmission
    double csiLatency = csiPacket.transmissionTime + 0.0005 * user.getId();
    latencies.push_back(csiLatency);

    // Parallel Data Transmission with increasing latency
    double dataLatency = 0.015 + 0.001 * user.getId();
    latencies.push_back(dataLatency);

    throughput += efficiencyFactor * (dataPacket.size * 8) / (dataLatency * 1e6); // Mbps
}

// WiFi6AP Implementation
WiFi6AP::WiFi6AP() : AccessPoint() {}

void WiFi6AP::transmit(User& user) {
    Packet dataPacket(PACKET_SIZE);

    // Simulate channel allocation with increasing efficiency and latency
    for (double subChannel : subChannelWidths) {
        double subChannelBandwidth = subChannel; // Sub-channel width in Hz
        double transmissionTime = 0.005 + 0.0002 * user.getId(); // OFDMA latency increase
        latencies.push_back(transmissionTime);

        // Throughput increases with more subchannels and users
        double efficiencyFactor = 1 + 0.03 * user.getId();
        throughput += efficiencyFactor * (dataPacket.size * 8) / (transmissionTime * 1e6); // Mbps
    }
}
