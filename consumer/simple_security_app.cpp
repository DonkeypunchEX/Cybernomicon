// consumer/simple_security_app.cpp
#include "security_monitor.hpp"
#include <iostream>
#include <thread>

int main() {
    std::cout << "🔒 Simple Security Monitor\n";
    std::cout << "=========================\n\n";
    
    consumer::security::SimpleMonitor monitor;
    
    // Quick security check
    std::cout << "Running security checks...\n";
    
    consumer::security::SecurityChecklist checklist = 
        consumer::security::SecurityChecklist::basic_system_hardening();
    
    auto results = checklist.run_checks();
    
    int passed = 0;
    int failed = 0;
    
    for (const auto& [check, result] : results) {
        if (result) {
            std::cout << "✓ " << check.description << "\n";
            passed++;
        } else {
            std::cout << "✗ " << check.description << "\n";
            std::cout << "  Fix: " << check.fix_guidance << "\n\n";
            failed++;
        }
    }
    
    std::cout << "\nResults: " << passed << " passed, " 
              << failed << " failed\n";
    
    if (failed > 0) {
        std::cout << "\n⚠️  Security issues found!\n";
        std::cout << "Run 'security-monitor --fix' to apply fixes\n";
    } else {
        std::cout << "\n✅ All security checks passed!\n";
    }
    
    // Start real-time monitoring
    char choice;
    std::cout << "\nStart real-time monitoring? (y/n): ";
    std::cin >> choice;
    
    if (choice == 'y' || choice == 'Y') {
        std::cout << "Starting monitoring...\n";
        
        // Monitor common attack vectors
        monitor.enable_real_time_protection(true);
        monitor.set_sensitivity(7);
        monitor.enable_notifications(true);
        
        std::vector<std::string> suspicious_patterns = {
            "rm -rf", "format", "chmod 777",
            "passwd", "shadow", "etc/shadow"
        };
        
        monitor.monitor_file("/var/log", suspicious_patterns);
        
        std::cout << "Monitoring active. Press Enter to stop...\n";
        std::cin.ignore();
        std::cin.get();
        
        auto alerts = monitor.get_recent_alerts();
        if (!alerts.empty()) {
            std::cout << "\nRecent alerts:\n";
            for (const auto& alert : alerts) {
                std::cout << "[" << alert.timestamp << "] "
                         << alert.title << "\n";
            }
        }
    }
    
    return 0;
}
