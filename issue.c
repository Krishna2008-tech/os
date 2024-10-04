#include <netdb.h>        // For network-related functions and structs
#include <stdio.h>        // Standard I/O functions for printing results
#include <arpa/inet.h>    // For IP address conversion functions (inet_pton, inet_ntoa)
#include <string.h>       // String manipulation functions (strcpy, strcmp)
#include <stdlib.h>       // Memory allocation functions (malloc, free)

// Placeholder DNS Query Function
// This function simulates a DNS lookup for a given hostname and returns
// the corresponding IP address as a string. In a real-world implementation,
// this would be replaced by an actual DNS query using the OS's resolver system.
int query_dns(const char *hostname, char *ip_addr) {
    // Simulate DNS lookup by checking if the hostname is "example.com"
    if (strcmp(hostname, "example.com") == 0) {
        // Set the IP address for example.com
        strcpy(ip_addr, "93.184.216.34");  // Hardcoded IP for example.com
        return 0;  // Return 0 to indicate success
    }
    // If hostname does not match, return an error (-1) to indicate failure
    return -1;  // Host not found
}

// Function to retrieve information about a host
// This function mimics `gethostent()` by returning a `struct hostent`
// that contains details about a host, such as its name and associated IP addresses.
// In this example, it retrieves information for a single hardcoded host ("example.com").
// In a full implementation, this would likely be more dynamic and support real DNS lookups.
struct hostent *gethostent() {
    static struct hostent host;  // Static struct to hold host information
    char *hostname = "example.com";  // In this example, the hostname is hardcoded

    // Allocate memory for the hostname (h_name) and copy the string
    host.h_name = malloc(strlen(hostname) + 1);  // +1 for the null-terminator
    strcpy(host.h_name, hostname);  // Copy the hostname into h_name

    // Allocate memory for the address list (h_addr_list)
    // This list stores the IP addresses associated with the host.
    // We allocate space for two pointers: one for the IP address and one for the null terminator.
    char **addr_list = malloc(2 * sizeof(char *));  
    addr_list[1] = NULL;  // The address list should be NULL-terminated

    // Perform DNS query using the placeholder function `query_dns()`
    char ip_str[INET_ADDRSTRLEN];  // Buffer to hold the IP address in string form
    if (query_dns(hostname, ip_str) == 0) {  // Query DNS and check for success
        // If the query is successful, convert the IP string (e.g., "93.184.216.34") to binary form
        struct in_addr *addr = malloc(sizeof(struct in_addr));  // Allocate memory for the IP address
        inet_pton(AF_INET, ip_str, addr);  // Convert the IP address from text to binary form

        // Store the address in the address list
        addr_list[0] = (char *)addr;  // Cast to char* as required by h_addr_list
        host.h_addr_list = addr_list;  // Assign the address list to the hostent struct

        // Set the address type and length in the hostent struct
        host.h_addrtype = AF_INET;  // Address family: AF_INET for IPv4 addresses
        host.h_length = sizeof(struct in_addr);  // Length of the address (4 bytes for IPv4)
    } else {
        // If the DNS query fails, clean up any allocated memory and return NULL
        free(host.h_name);  // Free the allocated memory for the hostname
        free(addr_list);    // Free the allocated memory for the address list
        return NULL;  // Return NULL to indicate failure
    }

    // Return a pointer to the filled-out `hostent` struct
    return &host;
}

// Main function for testing
// This function demonstrates how to use the `gethostent()` function
// by calling it and printing the host's name and IP address.
int main() {
    struct hostent *host = gethostent();  // Call gethostent to retrieve host information

    // Check if the host information was successfully retrieved
    if (host) {
        // Print the hostname and IP address
        printf("Host name: %s\n", host->h_name);  // Print the official name of the host
        // Print the IP address in human-readable form (dotted-decimal notation)
        printf("IP Address: %s\n", inet_ntoa(*(struct in_addr *)host->h_addr_list[0]));

        // Free the allocated memory after use to avoid memory leaks
        free(host->h_name);          // Free the memory allocated for the hostname
        free(host->h_addr_list[0]);  // Free the memory allocated for the IP address
        free(host->h_addr_list);     // Free the memory allocated for the address list
    } else {
        // If `gethostent()` returned NULL, print an error message
        printf("Failed to retrieve host information.\n");
    }

    return 0;  // Exit the program successfully
}
