/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2017-2018.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#include "guiQt/editor/SListView.hpp"

#include <fwCom/Signal.hxx>
#include <fwCom/Slots.hxx>

#include <fwCore/base.hpp>

#include <fwGuiQt/container/QtContainer.hpp>

#include <fwServices/macros.hpp>

#include <QEvent>
#include <QHBoxLayout>
#include <QKeyEvent>

namespace guiQt
{
namespace editor
{
fwServicesRegisterMacro( ::fwGui::editor::IEditor, ::guiQt::editor::SListView );

const ::fwCom::Signals::SignalKeyType SListView::s_ITEM_ADDED_SIG          = "itemAdded";
const ::fwCom::Signals::SignalKeyType SListView::s_ITEM_REMOVED_SIG        = "itemRemoved";
const ::fwCom::Signals::SignalKeyType SListView::s_ITEM_DOUBLE_CLICKED_SIG = "itemDoubleClicked";

const ::fwCom::Slots::SlotKeyType SListView::s_INSERT_ITEM_SLOT = "insertItem";
const ::fwCom::Slots::SlotKeyType SListView::s_REMOVE_ITEM_SLOT = "removeItem";

//------------------------------------------------------------------------------

SListView::SListView() noexcept
{
    newSignal< ItemAddedSignalType>(s_ITEM_ADDED_SIG);
    newSignal< ItemRemovedSignalType>(s_ITEM_REMOVED_SIG);
    newSignal< ItemDoubleClickedSignalType>(s_ITEM_DOUBLE_CLICKED_SIG);

    newSlot(s_INSERT_ITEM_SLOT, &SListView::insertItem, this);
    newSlot(s_REMOVE_ITEM_SLOT, &SListView::removeItem, this);
}

//------------------------------------------------------------------------------

SListView::~SListView() noexcept
{
}

//------------------------------------------------------------------------------

bool SListView::eventFilter(QObject* watched, QEvent* event)
{
    // filter suppr key release event in order to delete the current selected item of the list.
    if(watched == m_listWidget && event->type() == QEvent::KeyRelease)
    {
        QKeyEvent* eventKey = static_cast<QKeyEvent*>(event);
        if(eventKey->key() == Qt::Key_Delete)
        {
            const QList<QListWidgetItem*>& listItem = m_listWidget->selectedItems();
            if(listItem.size() > 0)
            {
                this->removeItem(m_listWidget->row(listItem.first()));
                return true;
            }
        }
    }
    return false;
}

//------------------------------------------------------------------------------
void SListView::configuring()
{
    this->initialize();

}

//------------------------------------------------------------------------------
void SListView::starting()
{
    this->create();
    ::fwGuiQt::container::QtContainer::sptr qtContainer =
        ::fwGuiQt::container::QtContainer::dynamicCast(this->getContainer());

    QPointer<QHBoxLayout> layout = new QHBoxLayout();
    layout->setObjectName("SListViewLayout");
    m_listWidget = new(QListWidget);
    m_listWidget->setObjectName("SListViewWidget");
    m_listWidget->installEventFilter(this);
    layout->addWidget( m_listWidget );

    connect(m_listWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this,
            SLOT(onItemDoubleClicked(QListWidgetItem*)));

    qtContainer->setLayout(layout);
}

//------------------------------------------------------------------------------

void SListView::stopping()
{
    SLM_TRACE_FUNC();

    this->destroy();
}
//------------------------------------------------------------------------------

void SListView::updating()
{
}

//------------------------------------------------------------------------------

void SListView::swapping()
{
    this->updating();
}

//------------------------------------------------------------------------------
void SListView::insertItem(int index, std::string value)
{
    // insert item at the index position of the list
    QListWidgetItem* newItem = new QListWidgetItem(QString::fromStdString(value));
    m_listWidget->insertItem(index, newItem);

    // notify
    this->signal<ItemAddedSignalType>(s_ITEM_ADDED_SIG)->asyncEmit(index);
}

//------------------------------------------------------------------------------
void SListView::removeItem(int index)
{
    // remove item at index position
    delete m_listWidget->takeItem(index);

    // notify
    this->signal<ItemRemovedSignalType>(s_ITEM_REMOVED_SIG)->asyncEmit(index);
}

//------------------------------------------------------------------------------

void SListView::onItemDoubleClicked(QListWidgetItem* item)
{
    const int index = m_listWidget->row(item);
    this->signal<ItemDoubleClickedSignalType>(s_ITEM_DOUBLE_CLICKED_SIG)->asyncEmit(index);
}

//------------------------------------------------------------------------------

} //namespace editor
} //namespace guiQt
