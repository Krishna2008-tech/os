# Wish List

If you're looking for a way to contribute to Minoca OS, but aren't sure where to start, this is the page for you. Below you'll find our current list of things we'd like to do but could use help with. We try to keep this list up to date. The General category lists abstract tasks that are always useful and can be anywhere on the map in terms of difficulty level. We've divided the more concrete tasks into three different difficulty levels. They're rough estimates and vague categories, as software is notoriously difficult to cost. Your mileage may vary. Within a category, tasks are in no particular order.

If you're serious about tackling one of the medium or hard tasks, feel free to shoot us an email first. We'll be able to provide a more detailed description, some context, and can offer suggestions towards getting started on any particular task.

Questions or patches can be submitted to minoca-dev@googlegroups.com. Good luck!

### General
 - Fix a bug
 - Port a new package over
 - Adopt a package: Clean up package diffs and work with maintainers to push upstream
 - Update a package to a newer version
 - Adopt a device: write a device driver
 - Port the OS to a new SoC or board
 - Write a test

### Easy
 - Fix a "TODO" in the code
 - Port a new package
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

 - AARCH64 disassembler
 - Implement hardware breakpoints in debugger/Kd
 - Floating point register access in debugger
 - Implement ResourceLimit*
 - Rework kernel device interface database
 - Serial (UART) device drivers

### Medium
 - Add TCP_CORK
 - Implement sigaltstack
 - Implement vfork
 - Implement statvfs
 - Implement pathconf
 - Add ATAPI to ATA driver
 - Isochronous USB transfers
 - Rework kernel support for user mode debugging/ptrace
 - Network bridge support
 - Virtual network devices
 - Namespaces
 - SD/MMC hardening (error recovery)
 - Crash dumps (application)
 - User mode profiling support
 - Mount improvements (flags, passing arguments to FS, C library integration)
 - Loopback block devices
 - UART flow control
 - Network/ramdisk boot
 - Add SD driver for PL081 used by Qemu (ARM).
 - NAND flash file system
 - IPv6 kernel support

### Hard
 - Implement better scheduling
 - Debugger 2.0
 - Port Clang
 - Port Go
 - Port Rust
 - Bluetooth stack
 - Audio stack
 - Crash Dumps (kernel)
 - Add support for better FS
 - AARCH64 architecture port
 - CD boot
 - Accelerated graphics

Below is a list of platforms that might be interesting to port to.
### Interesting Platform Ports
 - chipPC
 - Odroid C1/C2/XU4

### Community feature requests
 - PowerPC architecture port
 - MIPS architecture port
 - RISC-V architecture port
 - Asynchronous I/O mechanism
 - Port D package
