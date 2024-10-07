// json_output.h

#ifndef JSON_OUTPUT_H
#define JSON_OUTPUT_H

#include <fstream>
#include <string>     // Ensure this is included
#include "json.hpp"   // Include the JSON library
//#include "ITG.h"      // Include the definition of struct info


// Use nlohmann::json namespace
using json = nlohmann::json;

// Function to initialize the JSON output
void initialize_json_output(const std::string& filename);

// Function to process a packet and add it to the JSON data
void process_packet_to_json(const struct info* packetInfo);

// Function to finalize and write the JSON data to the file
void finalize_json_output();

#endif // JSON_OUTPUT_H
