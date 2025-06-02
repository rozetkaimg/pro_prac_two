#ifndef PATIENT_QUEUE_H
#define PATIENT_QUEUE_H

#include <string>
#include <vector>
#include <optional>
#include <algorithm>
#include <iostream>
#include <iomanip>


enum class ProcedureType {
    BLOOD_TESTS,
    MRI,
    ULTRASOUND,
    XRAY,
    UNKNOWN
};

struct Patient;


ProcedureType stringToProcedureType(const std::string& type_str);
std::string procedureTypeToString(ProcedureType type_enum);
int getProcedureTypeSortPriority(ProcedureType type_enum);
struct Patient {
    std::string medical_card_id;
    ProcedureType procedure_type_enum;
    std::string original_procedure_type_str;
    std::optional<std::string> mri_appointment_date;
    size_t original_index;
    Patient(std::string id, const std::string& proc_type_str, 
            std::optional<std::string> mri_date, size_t original_idx)
        : medical_card_id(std::move(id)),
          original_procedure_type_str(proc_type_str),
          mri_appointment_date(std::move(mri_date)),
          original_index(original_idx) {
        procedure_type_enum = stringToProcedureType(proc_type_str);
        if (procedure_type_enum != ProcedureType::MRI) {
            mri_appointment_date.reset();
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const Patient& p);
};

void formPatientQueue(std::vector<Patient>& patients);
void printPatientQueue(const std::string& title, const std::vector<Patient>& queue);
#endif // PATIENT_QUEUE_H