// json_output.cpp

#include <iostream>   // Add this line
#include <string>     // Add this line if not already included
#include "json_output.h"
#include "ITG.h"
#include <zlib.h>  


// JSON output file stream
// static std::ofstream jsonOut;
static gzFile jsonOut;

// JSON data structure
static json jsonData;
// Flag to check if it's the first packet
static bool firstPacket = true;

// Function to initialize the JSON output
void initialize_json_output(const std::string& filename) {
    // Open the JSON output gzip file
    jsonOut = gzopen(filename.c_str(), "wb");  // Open for writing in binary mode with compression
    if (jsonOut == nullptr) {
        std::cerr << "Error opening JSON output file: " << filename << std::endl;
        exit(1);
    }
    // Start the JSON array
    std::string header = "{\n\"oneway_trips\": [\n";
    gzwrite(jsonOut, header.c_str(), header.size());
    firstPacket = true;
}


// Function to process a packet and add it to the JSON data
void process_packet_to_json(const struct info* packetInfo) {
    // Calculate send and receive timestamps in nanoseconds
    uint64_t client_send_wall = static_cast<uint64_t>(
        (packetInfo->txTime1 * 3600 + packetInfo->txTime2 * 60 + packetInfo->txTime3) * 1e9);

    uint64_t server_receive_wall = static_cast<uint64_t>(
        (packetInfo->rxTime1 * 3600 + packetInfo->rxTime2 * 60 + packetInfo->rxTime3) * 1e9);

    // Calculate the send delay in nanoseconds
    uint64_t send_delay = server_receive_wall - client_send_wall;

    // Create a JSON object for this packet
    json packetJson = {
        {"seqno", packetInfo->seqNum},
        {"timestamps", {
            {"client", {
                {"receive", json::object()},  // Empty object
                {"send", {
                    {"wall", client_send_wall}
                }}
            }},
            {"server", {
                {"receive", {
                    {"wall", server_receive_wall}
                }},
                {"send", json::object()}
            }}
        }},
        {"delay", {
            {"send", send_delay}
        }}
    };

    // Serialize the JSON object to a string
    std::string jsonString = packetJson.dump(4);  // Indent with 4 spaces

    // If not the first packet, prepend a comma and newline
    if (!firstPacket) {
        std::string comma = ",\n";
        gzwrite(jsonOut, comma.c_str(), comma.size());
    } else {
        firstPacket = false;
    }

    // Write the JSON string to the gzip file
    gzwrite(jsonOut, jsonString.c_str(), jsonString.size());
}


// Function to finalize and write the JSON data to the file
void finalize_json_output() {
    // Close the JSON array and object
    std::string footer = "\n]\n}";
    gzwrite(jsonOut, footer.c_str(), footer.size());
    gzclose(jsonOut);
}

