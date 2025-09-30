#include "Customer.h"
#include <sstream>
#include <stdexcept>
#include <vector>
#include <cstdlib>
#include <cctype>

// Default compare option
CustomerCompareOptions Customer::compareWith = FullName;

// --- small helpers ---
static inline std::string trim(const std::string& s) {
    size_t i = 0, j = s.size();
    while (i < j && std::isspace(static_cast<unsigned char>(s[i]))) ++i;
    while (j > i && std::isspace(static_cast<unsigned char>(s[j-1]))) --j;
    return s.substr(i, j - i);
}

static std::vector<std::string> splitTSV(const std::string& line) {
    std::vector<std::string> out;
    std::string cur;
    for (char c : line) {
        if (c == '\t') { out.push_back(cur); cur.clear(); }
        else { cur.push_back(c); }
    }
    out.push_back(cur);
    return out;
}

// ===== Constructors =====
Customer::Customer() : customer_since("1/1/1970"), date_of_birth("1/1/1970") {}

Customer::Customer(std::string id, std::string user, std::string first, std::string last,
                   std::string addr, std::string cty, std::string st, std::string postal,
                   std::string email, std::string gen, std::string comp, std::string job,
                   Date since, std::string ssn, Date dob,
                   int income, int credit, double sales)
    : customer_id(std::move(id)), username(std::move(user)), first_name(std::move(first)), last_name(std::move(last)),
      street_address(std::move(addr)), city(std::move(cty)), state(std::move(st)), postal_code(std::move(postal)),
      email_address(std::move(email)), gender(std::move(gen)), company(std::move(comp)), job_title(std::move(job)),
      customer_since(since), social_security_number(std::move(ssn)), date_of_birth(dob),
      household_income(income), credit_score(credit), total_sales(sales) {}

Customer::Customer(std::string record) : customer_since("1/1/1970"), date_of_birth("1/1/1970") {
    // Expected field order (17 fields):
    // customer_id, username, first_name, last_name, street_address, city, state, postal_code,
    // email_address, gender, company, job_title, customer_since, social_security_number,
    // date_of_birth, household_income, credit_score, total_sales
    // NOTE: The prompt lists 18+ fields with total_sales last. We'll accept either 18 (preferred) or 17
    // and compute totals accordingly (robustness).
    auto cols = splitTSV(record);
    if (cols.size() < 18) {
        // Some datasets list 18 fields exactly. If fewer, throw to catch bad lines early.
        throw std::runtime_error("Bad TSV record: wrong number of fields");
    }

    customer_id             = trim(cols[0]);
    username                = trim(cols[1]);
    first_name              = trim(cols[2]);
    last_name               = trim(cols[3]);
    street_address          = trim(cols[4]);
    city                    = trim(cols[5]);
    state                   = trim(cols[6]);
    postal_code             = trim(cols[7]);
    email_address           = trim(cols[8]);
    gender                  = trim(cols[9]);
    company                 = trim(cols[10]);
    job_title               = trim(cols[11]);

    // Dates via your Date(string) ctor (expects "mm/dd/yyyy")
    customer_since          = Date(trim(cols[12]));
    social_security_number  = trim(cols[13]);
    date_of_birth           = Date(trim(cols[14]));

    // Numbers
    household_income        = std::atoi(trim(cols[15]).c_str());
    credit_score            = std::atoi(trim(cols[16]).c_str());
    total_sales             = std::atof(trim(cols[17]).c_str());
}

// ===== Getters/Setters =====
void Customer::setCustomerID(std::string v) { customer_id = std::move(v); }
std::string Customer::getCustomerID() { return customer_id; }

std::string Customer::getUserName() { return username; }
void Customer::setUserName(std::string v) { username = std::move(v); }

std::string Customer::getFirstName() const { return first_name; }
void Customer::setFirstName(std::string v) { first_name = std::move(v); }

std::string Customer::getLastName() const { return last_name; }
void Customer::setLastName(std::string v) { last_name = std::move(v); }

std::string Customer::getStreetAddress() const { return street_address; }
void Customer::setStreetAddress(std::string v) { street_address = std::move(v); }

std::string Customer::getCity() const { return city; }
void Customer::setCity(std::string v) { city = std::move(v); }

std::string Customer::getState() const { return state; }
void Customer::setState(std::string v) { state = std::move(v); }

std::string Customer::getPostalCode() const { return postal_code; }
void Customer::setPostalCode(std::string v) { postal_code = std::move(v); }

std::string Customer::getEmail() const { return email_address; }
void Customer::setEmail(std::string v) { email_address = std::move(v); }

std::string Customer::getGender() const { return gender; }
void Customer::setGender(std::string v) { gender = std::move(v); }

std::string Customer::getCompany() const { return company; }
void Customer::setCompany(std::string v) { company = std::move(v); }

std::string Customer::getJobTitle() const { return job_title; }
void Customer::setJobTitle(std::string v) { job_title = std::move(v); }

void Customer::setSocialSecurityNumber(std::string v) { social_security_number = std::move(v); }
std::string Customer::getSocialSecurityNumber() { return social_security_number; }

Date Customer::getCustomerSince() const { return customer_since; }
void Customer::setCustomerSince(Date v) { customer_since = v; }

Date Customer::getDateOfBirth() const { return date_of_birth; }
void Customer::setDateOfBirth(Date v) { date_of_birth = v; }

int Customer::getHouseholdIncome() const { return household_income; }
void Customer::setHouseholdIncome(int v) { household_income = v; }

int Customer::getCreditScore() const { return credit_score; }
void Customer::setCreditScore(int v) { credit_score = v; }

double Customer::getTotalSales() const { return total_sales; }
void Customer::setTotalSales(double v) { total_sales = v; }

// ===== Compare mode =====
CustomerCompareOptions Customer::getCompareWith() { return compareWith; }
void Customer::setCompareWith(CustomerCompareOptions code) { compareWith = code; }

// ===== Stringify =====
std::string Customer::toString() const {
    return first_name + " " + last_name + " (" + customer_id + ")";
}

// ===== three-way compare =====
int Customer::threeWayCompare(const Customer& rhs) const {
    auto sgn = [](long long x) -> int { return (x < 0) ? -1 : (x > 0 ? 1 : 0); };

    switch (compareWith) {
        case FullName: {
            // Sort by Last, then First (stable, readable)
            std::string a = last_name + "\x1F" + first_name;   // \x1F just to avoid accidental collisions
            std::string b = rhs.last_name + "\x1F" + rhs.first_name;
            if (a < b) return -1; if (a > b) return 1; break;
        }
        case UserName:
            if (username < rhs.username) return -1; if (username > rhs.username) return 1; break;
        case CustomerID:
            if (customer_id < rhs.customer_id) return -1; if (customer_id > rhs.customer_id) return 1; break;
        case CustomerSince:
            // Earlier date = "less" (has been a customer longer) — matches the example logic
            if (customer_since < rhs.customer_since) return -1;
            if (customer_since > rhs.customer_since) return 1;
            break;
        case DateOfBirth:
            // Earlier DOB = "less" (older is less). Younger will be "greater".
            if (date_of_birth < rhs.date_of_birth) return -1;
            if (date_of_birth > rhs.date_of_birth) return 1;
            break;
        case CreditScore:
            return sgn(static_cast<long long>(credit_score) - rhs.credit_score);
        case HouseholdIncome:
            return sgn(static_cast<long long>(household_income) - rhs.household_income);
        case TotalSales: {
            if (total_sales < rhs.total_sales) return -1;
            if (total_sales > rhs.total_sales) return 1;
            break;
        }
    }
    // Tie-breaker for strict weak ordering
    if (customer_id < rhs.customer_id) return -1;
    if (customer_id > rhs.customer_id) return 1;
    return 0;
}

// ===== Relational operators =====
bool Customer::operator==(const Customer& rhs) const { return threeWayCompare(rhs) == 0; }
bool Customer::operator!=(const Customer& rhs) const { return threeWayCompare(rhs) != 0; }
bool Customer::operator<(const Customer& rhs)  const { return threeWayCompare(rhs) < 0; }
bool Customer::operator<=(const Customer& rhs) const { return threeWayCompare(rhs) <= 0; }
bool Customer::operator>(const Customer& rhs)  const { return threeWayCompare(rhs) > 0; }
bool Customer::operator>=(const Customer& rhs) const { return threeWayCompare(rhs) >= 0; }

// ===== stream operator =====
std::ostream& operator<<(std::ostream& out, const Customer& customer) {
    return out << customer.toString();
}

