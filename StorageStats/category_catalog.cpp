#include "category_catalog.h"

std::vector<CategoryCatalog::DomainSection> CategoryCatalog::_sections = {
   {DomainFilter::dfSpecialties, "specialty"},
   {DomainFilter::dfSpecializations, "specialization"},
   {DomainFilter::dfStartYears, "year_start"},
   {DomainFilter::dfYears, "year"},
   {DomainFilter::dfKurs, "kurs"},
   {DomainFilter::dfGroups, "group"},
   {DomainFilter::dfTerms, "term"},
   {DomainFilter::dfTeachers, "teacher"},
   {DomainFilter::dfSubjects, "subject"},
   {DomainFilter::dfFaculties, "faculty"},
   {DomainFilter::dfExamOrder, "exam"}
};
