#include "patient_queue.h"



ProcedureType stringToProcedureType(const std::string& type_str) {
    if (type_str == "Анализы крови") return ProcedureType::BLOOD_TESTS;
    if (type_str == "МРТ") return ProcedureType::MRI;
    if (type_str == "УЗИ") return ProcedureType::ULTRASOUND;
    if (type_str == "Рентген") return ProcedureType::XRAY;
    return ProcedureType::UNKNOWN;
}
std::string procedureTypeToString(ProcedureType type_enum) {
    switch (type_enum) {
        case ProcedureType::BLOOD_TESTS: return "Анализы крови";
        case ProcedureType::MRI:         return "МРТ";
        case ProcedureType::ULTRASOUND:  return "УЗИ";
        case ProcedureType::XRAY:        return "Рентген";
        default:                         return "Неизвестно";
    }
}
int getProcedureTypeSortPriority(ProcedureType type_enum) {
    switch (type_enum) {
        case ProcedureType::BLOOD_TESTS: return 0;
        case ProcedureType::MRI:         return 1;
        case ProcedureType::ULTRASOUND:  return 2;
        case ProcedureType::XRAY:        return 3;
        default:                         return 4;
    }
}
std::ostream& operator<<(std::ostream& os, const Patient& p) {
    os << "Карта: " << std::setw(8) << std::left << p.medical_card_id
       << "| Тип: " << std::setw(15) << std::left << procedureTypeToString(p.procedure_type_enum);
    if (p.procedure_type_enum == ProcedureType::MRI && p.mri_appointment_date.has_value()) {
        os << "| Дата МРТ: " << std::setw(12) << std::left << p.mri_appointment_date.value();
    } else {
        os << "| " << std::setw(23) << std::left << "";
    }
    os << "| (Исходный №: " << p.original_index + 1 << ")";
    return os;
}
void formPatientQueue(std::vector<Patient>& patients) {
    std::stable_sort(patients.begin(), patients.end(),
        [](const Patient& a, const Patient& b) {
            int priority_a = getProcedureTypeSortPriority(a.procedure_type_enum);
            int priority_b = getProcedureTypeSortPriority(b.procedure_type_enum);
            if (priority_a != priority_b) {
                return priority_a < priority_b;
            }
            if (a.procedure_type_enum == ProcedureType::MRI) {
                if (a.mri_appointment_date.has_value() && !b.mri_appointment_date.has_value()) return true;
                if (!a.mri_appointment_date.has_value() && b.mri_appointment_date.has_value()) return false;
                if (a.mri_appointment_date.has_value() && b.mri_appointment_date.has_value()) {
                    if (a.mri_appointment_date.value() != b.mri_appointment_date.value()) {
                        return a.mri_appointment_date.value() < b.mri_appointment_date.value();
                    }
                }
            }
            return false;
        }
    );
}
void printPatientQueue(const std::string& title, const std::vector<Patient>& queue) {
    std::cout << "--- " << title << " ---" << std::endl;
    if (queue.empty()) {
        std::cout << "(Очередь пуста)" << std::endl;
    } else {
        for (const auto& patient : queue) {
            std::cout << patient << std::endl;
        }
    }
    std::cout << std::string(title.length() + 6, '-') << std::endl; // Dynamic separator length
}
