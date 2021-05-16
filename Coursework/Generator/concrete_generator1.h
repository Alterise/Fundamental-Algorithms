#include "generator_interface.h"
#include "date.h"

class generator1 : public generator_interface {
public:
    ~generator1() {

    }
    Document generate() {
        document current_document;

        return current_document;
    };
private:
    long long generate_long_long(int length) {

    }

    int generate_int(int length) {

    }

    int generate_fiscal_year() {

    }

    Date generate_filling_date() {

    }

    Date generate_birth_date() {

    }

    Date generate_passport_date() {

    }

    std::string generate_tax_authority() {

    }

    std::string generate_name() {

    }

    std::string generate_surname() {

    }

    std::string generate_patronymic() {

    }

    char generate_gender() {

    }

    std::string generate_country() {

    }

    std::string generate_region() {

    }

    std::string generate_city() {

    }

    std::string generate_street() {

    }
};