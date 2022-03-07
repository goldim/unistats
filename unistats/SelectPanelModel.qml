import QtQuick 2.0

ListModel{
    id : it
    signal sortEvent(var order)
    onSortEvent: {
        var newOrder = [];
        for (var i = 0; i < it.count; i++)
        {
            newOrder.push({id : it.get(i).id, val: it.get(i).name});
        }
        var res = sort(newOrder, order);

        it.clear();

        for (var key in newOrder){
            it.append({id : newOrder[key].id, name : newOrder[key].val});
        }
    }

    function sort(arr, order){
        switch (order){
        case Qt.AscendingOrder:
            arr.sort(function(a, b){
                return a.val === b.val ? 0 : +(a.val > b.val) || -1;
            });
            break;
        case Qt.DescendingOrder:
            arr.sort(function(a, b){
                return a.val === b.val ? 0 : +(a.val < b.val) || -1;
            });
            break;
        }

        return arr;
    }
}
