import QtQuick
import QtQuick.Layouts

Component {
    id: delegate_list_view

       Item {
           id: delegate_item
           width: rect_delegate_text.delegate_text.contentWidth + 10
           height: rect_delegate_text.delegate_text.contentHeight + 10

           LabelsTextForDelegate{
               id: rect_delegate_text
           }
       }
}
