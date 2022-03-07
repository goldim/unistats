import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3

import "models" as Models

Item {    
//    signal chooseModel(var id, var extraId)
    signal chooseModel(var id, var idFrom)

    Models.Category{
        id : groupsM
    }

    Models.Category{
        id : teachersM
    }

    Models.Category{
        id : yearsM
    }

    Models.Category{
        id : termsM
    }

    Models.Category{
        id : kursM
    }

    Models.Category{
        id : subjectsM
    }

    Models.Category {
        id : facultiesM
    }

    Models.Category {
        id : specialtiesM
    }

    Models.Category {
        id : specializationsM
    }

    Models.Category{
        id : startYearsM
    }

    ListModel {
        id : specialtyByFacultyM
        function loadItems(){
        }
    }

    function activate()
    {
        fromItemsForChoose.Layout.fillWidth = true;
        fromItemsForChoose.model = facultiesM;
        fromItemsForChoose.outputPanel = itemsForChoose;
        fromItemsForChoose.clearPanel = chosenItems;
    }

    function deactivate()
    {
        fromItemsForChoose.Layout.fillWidth = false;
    }

    onChooseModel: {
        if (idFrom === undefined)
        {
            deactivate();
        }
        else
        {
            activate();
        }

        itemsForChoose.clearAll()
        chosenItems.clearAll();

        var models = [yearsM, groupsM, teachersM, termsM, subjectsM,
                      kursM, facultiesM, specialtiesM,
                      specializationsM, startYearsM, specialtyByFacultyM];

        models[id].loadItems();

        for (var i = 0; i < models[id].count; i++)
            itemsForChooseM.append(models[id].get(i));
        itemsForChooseM.sortEvent(Qt.AscendingOrder);
    }

    function getChosenIDs(){
        var items = chosenItemsM;
        var IDs = [];
        for (var i = 0; i < items.count; i++)
        {
            IDs.push(items.get(i).id);
        }
        return IDs;
    }

    function getChosenNames(){
        var items = chosenItemsM;
        var names = [];
        for (var i = 0; i < items.count; i++)
        {
            names.push(items.get(i).name);
        }
        return names;
    }

    GridLayout {
        anchors.fill: parent
        columnSpacing : 0
        rowSpacing: 0
        columns: 3

        SimpleItemPanel{
            id: fromItemsForChoose

            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        ItemPanel{
            id: itemsForChoose            
            viewTitle: "Элементы для выбора"
            barElementsAlign : "right"
            toModel : chosenItemsM
            model : SelectPanelModel{
                id: itemsForChooseM                
            }

            Layout.fillWidth: true
            Layout.fillHeight: true
        }
        ItemPanel{
            id: chosenItems
            viewTitle: "Выбранные элементы"
            toModel : itemsForChooseM
            model: SelectPanelModel {
                id : chosenItemsM
            }
            barElementsAlign : "left"

            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }
}



