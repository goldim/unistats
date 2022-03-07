import QtQuick 2.0

ListModel {
    id : it
    signal loadItems    
    property bool bLoaded: false    

    function loadConcreteItems(idModel){
        if (idModel.bLoaded)
            return;
        var values = _controller.loadItems();                               

        idModel.bLoaded = true;

        for (var key in values)
        {
            idModel.append({id : key, name : values[key]});
//            console.info(key + " " +values[key]);
        }
    }

    onLoadItems: loadConcreteItems(it)
}

