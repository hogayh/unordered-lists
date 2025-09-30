#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include <ostream>
#include "Date.h"

// Make std names visible to tests that use plain `string`/`ostream`
using std::string;
using std::ostream;

enum CustomerCompareOptions {
    FullName,
    UserName,
    CustomerID,
    CustomerSince,
    DateOfBirth,
    CreditScore,
    HouseholdIncome,
    TotalSales
};

class Customer {
private:
    // Fields (match TSV order)
    string customer_id;
    string username;
    string first_name;
    string last_name;
    string street_address;
    string city;
    string state;
    string postal_code;
    string email_address;
    string gender;
    string company;
    string job_title;
    Date   customer_since;
    string social_security_number;
    Date   date_of_birth;
    int    household_income = 0;
    int    credit_score     = 0;
    double total_sales      = 0.0;

    // helper function to compare this customer with another one
    int threeWayCompare(const Customer& rhs) const;

    // shared comparison mode
    static CustomerCompareOptions compareWith;

public:
    // ===== Constructors =====
    Customer();
    Customer(string customer_id, string username, string first_name, string last_name,
             string street_address, string city, string state, string postalCode,
             string email, string gender, string company, string job_title,
             Date customer_since, string social_security_number, Date date_of_birth,
             int household_income, int credit_score, double total_sales);
    explicit Customer(string record); // TSV line

    // ===== Getters/Setters =====
    void setCustomerID(string customer_id);
    string getCustomerID();

    string getUserName();
    void setUserName(string username);

    string getFirstName() const;
    void setFirstName(string first_name);

    string getLastName() const;
    void setLastName(string last_name);

    string getStreetAddress() const;
    void setStreetAddress(string street_address);

    string getCity() const;
    void setCity(string city);

    string getState() const;
    void setState(string state);

    string getPostalCode() const;
    void setPostalCode(string postal_code);

    string getEmail() const;
    void setEmail(string email);

    string getGender() const;
    void setGender(string gender);

    string getCompany() const;
    void setCompany(string company);

    string getJobTitle() const;
    void setJobTitle(string job_title);

    void setSocialSecurityNumber(string social_security_number);
    string getSocialSecurityNumber();

    Date getCustomerSince() const;
    void setCustomerSince(Date customer_since);

    Date getDateOfBirth() const;
    void setDateOfBirth(Date date_of_birth);

    int getHouseholdIncome() const;
    void setHouseholdIncome(int household_income);

    int getCreditScore() const;
    void setCreditScore(int credit_score);

    double getTotalSales() const;
    void setTotalSales(double total_sales);

    // ===== Static compare mode =====
    static CustomerCompareOptions getCompareWith();
    static void setCompareWith(CustomerCompareOptions code);

    // ===== Stringify =====
    string toString() const;

    // ===== Relational operators =====
    bool operator==(const Customer& rhs) const;
    bool operator!=(const Customer& rhs) const;
    bool operator<(const Customer& rhs)  const;
    bool operator<=(const Customer& rhs) const;
    bool operator>(const Customer& rhs)  const;
    bool operator>=(const Customer& rhs) const;
};

// stream insertion (not a member)
ostream& operator<<(ostream& out, const Customer& customer);

#endif // CUSTOMER_H
