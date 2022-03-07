import QtQuick 2.0

ListModel
{
    ListElement { category: "Year"; text: "Год"}
    ListElement { category: "Group"; text: "Группа"}
    ListElement { category: "Teacher"; text: "Преподаватель"}
    ListElement { category: "Term"; text: "Семестр"}
    ListElement { category: "Subject"; text: "Дисциплина"}
    ListElement { category: "Kurs"; text: "Курс"}
    ListElement { category: "Faculty"; text: "Факультет"}
    ListElement { category: "Specialty"; text: "Специальность"}
    ListElement { category: "Specialization"; text: "Специализация"}
    ListElement { category: "YearStart"; text: "Год основания"}
    ListElement { category: "Specialty"; categoryfrom: "Faculty"; text: "Фак.->Специал."}
}
