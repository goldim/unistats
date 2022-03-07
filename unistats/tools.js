function categoryToDative(ctgry)
{
    var res;
    switch (ctgry)
    {
    case "Year":
        res = "годам";
        break;
    case "Term":
        res = "семестрам";
        break;
    case "Teacher":
        res = "преподавателям";
        break;
    case "Group":
        res = "группам";
        break;
    case "Subject":
        res = "дисциплинам";
        break;
    case "Kurs":
        res = "курсам";
        break;
    case "Faculty":
        res = "факультетам";
        break;
    case "Specialty":
        res = "специальностям";
        break;
    case "Specialization":
        res = "специализациям";
        break;
    case "YearStart":
        res = "годам основания";
        break;
    case "ExamOrder":
        res = "номерам экзаменов в сессии";
        break;
    default:
        res = "частотам";
    }
    return res;
}

function categoryToNominative(ctgry)
{
    var res;
    switch (ctgry)
    {
    case "Year":
        res = "год";
        break;
    case "Term":
        res = "семестр";
        break;
    case "Kurs":
        res = "курс";
        break;
    case "ExamOrder":
        res = "номер экзамена в сессии";
        break;
    case "YearStart":
        res = "год набора";
        break;
    }
    return res;
}

function getColor(i)
{
    var data = [
                "#209fdf",
                "#99ca53",
                "#f6a625",
                "#6d5fd5",
                "#bf593e",
                "#FFD700",
                "#000000",
                "#00FFFF",
                "#FF00FF",
                "#C0C0C0",
                "#808080",
                "#800080"
            ];
    var tmp = i;
    while (tmp >= data.length)
    {
        tmp = tmp - data.length;
    }

    return data[tmp];
}
