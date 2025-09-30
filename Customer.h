#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include <ostream>
#include <istream>

/**
 * @brief Minimal Customer that stores a name and an integer ID.
 *        Input format: "Name,ID" per line (e.g., "Alice,1001").
 */
class Customer {
public:
    Customer() = default;
    Customer(std::string name, int id) : name_(std::move(name)), id_(id) {}

    /// @return customer's display name
    const std::string& name() const { return name_; }
    /// @return customer's numeric ID
    int id() const { return id_; }

    /// Equality compares IDs (useful for search/delete).
    bool operator==(const Customer& rhs) const { return id_ == rhs.id_; }

    /// Prints "Name (ID)".
    friend std::ostream& operator<<(std::ostream& os, const Customer& c) {
        return os << c.name_ << " (" << c.id_ << ")";
    }

    /// Reads "Name,ID" from a single line.
    friend std::istream& operator>>(std::istream& is, Customer& c) {
        std::string line;
        if (!std::getline(is, line)) return is;
        if (line.empty()) return is;
        auto comma = line.find(',');
        std::string name = comma == std::string::npos ? line : line.substr(0, comma);
        std::string idstr = comma == std::string::npos ? "0" : line.substr(comma + 1);

        // light trim
        auto trim = [](std::string& s) {
            const char* ws = " \t\r\n";
            auto a = s.find_first_not_of(ws);
            auto b = s.find_last_not_of(ws);
            s = (a == std::string::npos) ? std::string() : s.substr(a, b - a + 1);
        };
        trim(name); trim(idstr);

        int id = 0;
        try { id = std::stoi(idstr); } catch (...) { id = 0; }

        c.name_ = std::move(name);
        c.id_ = id;
        return is;
    }

private:
    std::string name_;
    int id_{0};
};

#endif // CUSTOMER_H
