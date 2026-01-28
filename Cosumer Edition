// =============== CONSUMER EDITION ===============
// consumer/security_monitor.hpp

#pragma once

#include <string>
#include <vector>
#include <functional>
#include <memory>

namespace consumer::security {

class SimpleMonitor {
public:
    enum class AlertLevel {
        INFO,
        WARNING,
        CRITICAL
    };
    
    struct Alert {
        std::string title;
        std::string description;
        AlertLevel level;
        std::string timestamp;
        std::vector<std::string> recommendations;
    };
    
    SimpleMonitor();
    
    // Consumer-friendly API
    bool monitor_file(const std::string& path, 
                     const std::vector<std::string>& suspicious_patterns);
    
    bool monitor_network_traffic(const std::string& interface, 
                                int max_alerts_per_minute = 10);
    
    bool monitor_processes(const std::vector<std::string>& suspicious_processes);
    
    std::vector<Alert> get_recent_alerts(int max_alerts = 50) const;
    void clear_alerts();
    
    // Consumer features
    void enable_real_time_protection(bool enabled);
    void set_sensitivity(int level);  // 1-10
    void enable_notifications(bool enabled);
    
private:
    class Impl;
    std::unique_ptr<Impl> impl_;
};

// Simple, guided security check
class SecurityChecklist {
public:
    struct Check {
        std::string id;
        std::string description;
        std::function<bool()> checker;
        std::string fix_guidance;
    };
    
    SecurityChecklist();
    
    void add_check(Check check);
    std::vector<std::pair<Check, bool>> run_checks();
    void generate_report(const std::string& output_path);
    
    // Pre-built checklists
    static SecurityChecklist basic_system_hardening();
    static SecurityChecklist network_security();
    static SecurityChecklist application_security();
    
private:
    std::vector<Check> checks_;
};

} // namespace consumer::security
