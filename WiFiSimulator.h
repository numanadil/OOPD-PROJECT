#ifndef WIFISIMULATOR_H
#define WIFISIMULATOR_H

#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <numeric>
#include <algorithm>
#include <random>

const double BANDWIDTH = 20e6; // 20 MHz in Hz
const double MODULATION_RATE = log2(256); // 256-QAM
const double CODING_RATE = 5.0 / 6.0;
const int PACKET_SIZE = 1024; // 1 KB in bytes

class Packet {
public:
    int size; // Packet size in bytes
    double transmissionTime; // Transmission time in seconds
    Packet(int size);
};

class User {
protected:
    int id;
public:
    User(int id);
    int getId() const;
};

class AccessPoint {
protected:
    std::queue<Packet> packetQueue;
    std::vector<double> latencies;
    double throughput; // Mbps
    double avgLatency;
    double maxLatency;

public:
    AccessPoint();
    virtual void transmit(User& user) = 0; // Pure virtual function
    virtual void computeMetrics();
};

class WiFi4AP : public AccessPoint {
public:
    WiFi4AP();
    void transmit(User& user) override;
};

class WiFi5AP : public AccessPoint {
public:
    WiFi5AP();
    void transmit(User& user) override;
};

class WiFi6AP : public AccessPoint {
private:
    std::vector<double> subChannelWidths = {2e6, 4e6, 10e6}; // 2 MHz, 4 MHz, 10 MHz
public:
    WiFi6AP();
    void transmit(User& user) override;
};

#endif
