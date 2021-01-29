/*!
  @author Shin'ichiro Nakaoka
*/

#include "PyQObjectHolder.h"
#include "PyQString.h"
#include "PyQtSignal.h"
#include <QWidget>
#include <QLayout>
#include <QMainWindow>
#include <QPushButton>
#include <QToolButton>
#include <QCheckBox>
#include <QLabel>
#include <QSpinBox>
#include <QDialog>
#include <QFrame>
#include <QAbstractScrollArea>
#include <QMenu>

namespace py = pybind11;

namespace cnoid {

void exportPyQtGuiLayoutClasses(py::module m);
void exportPyQtGuiModelViewClasses(py::module m);

}

using namespace cnoid;

PYBIND11_MODULE(QtWidgets, m)
{
    m.doc() = "Choreonoid QtWidgets module";

    py::module::import("cnoid.QtCore");
    py::module::import("cnoid.QtGui");

    py::class_<QWidget, PyQObjectHolder<QWidget>, QObject>(m, "QWidget")
        .def("hasFocus", &QWidget::hasFocus)
        .def("isActiveWindow", &QWidget::isActiveWindow)
        .def("isAncestorOf", &QWidget::isAncestorOf)
        .def("isEnabled", &QWidget::isEnabled)
        .def("isEnabledTo", &QWidget::isEnabledTo)
        .def("isFullScreen", &QWidget::isFullScreen)
        .def("isHidden", &QWidget::isHidden)
        .def("isMaximized", &QWidget::isMaximized)
        .def("isMinimized", &QWidget::isMinimized)
        .def("isModal", &QWidget::isModal)
        .def("isVisible", &QWidget::isVisible)
        .def("isVisibleTo", &QWidget::isVisibleTo)
        .def("isWindow", &QWidget::isWindow)
        .def("isWindowModified", &QWidget::isWindowModified)
        .def("parentWidget", &QWidget::parentWidget)
        .def("setLayout", &QWidget::setLayout)
        .def("setParent",  (void (QWidget::*)(QWidget* parent)) &QWidget::setParent)
        .def("toolTip", &QWidget::toolTip)
        .def("setToolTip", &QWidget::setToolTip)
        .def("whatsThis", &QWidget::whatsThis)
        .def("setWhatsThis", &QWidget::setWhatsThis)
        .def("windowIconText", &QWidget::windowIconText)
        .def("setWindowIconText", &QWidget::setWindowIconText)
        .def("window", &QWidget::window)
        .def("windowFilePath", &QWidget::windowFilePath)
        .def("windowRole", &QWidget::windowRole)
        .def("windowTitle", &QWidget::windowTitle)

        // Public slots
        .def("close", &QWidget::close)
        .def("hide", &QWidget::hide)
        .def("lower", &QWidget::lower)
        .def("raise", &QWidget::raise)
        .def("repaint", (void (QWidget::*)()) &QWidget::repaint)
        .def("setDisabled", &QWidget::setDisabled)
        .def("setEnabled", &QWidget::setEnabled)
        .def("setFocus", (void (QWidget::*)()) &QWidget::setFocus)
        .def("setHidden", &QWidget::setHidden)
        .def("setVisible", &QWidget::setVisible)
        .def("setWindowModified", &QWidget::setWindowModified)
        .def("setWindowTitle", &QWidget::setWindowTitle)
        .def("show", &QWidget::show)
        .def("showFullScreen", &QWidget::showFullScreen)
        .def("showMaximized", &QWidget::showMaximized)
        .def("showMinimized", &QWidget::showMinimized)
        .def("showNormal", &QWidget::showNormal)
        .def("update",  (void (QWidget::*)()) &QWidget::update)
        ;

    py::class_<QMainWindow, PyQObjectHolder<QMainWindow>, QWidget>(m, "QMainWindow");

    py::class_<QAbstractButton, PyQObjectHolder<QAbstractButton>, QWidget> qAbstractButton(m, "QAbstractButton");

    typedef cnoid::QtSignal<void(QAbstractButton::*)(bool), void()> ButtonClickSignal;
    cnoid::PyQtSignal<ButtonClickSignal>(qAbstractButton, "ClickSignal");
    typedef cnoid::QtSignal<void(QAbstractButton::*)(bool), void(bool)> ButtonBoolSignal;
    cnoid::PyQtSignal<ButtonBoolSignal>(qAbstractButton, "BoolSignal");

    qAbstractButton
        .def("autoExclusive", &QAbstractButton::autoExclusive)
        .def("setAutoExclusive", &QAbstractButton::setAutoExclusive)
        .def("autoRepeat", &QAbstractButton::autoRepeat)
        .def("setAutoRepeat", &QAbstractButton::setAutoRepeat)
        .def("autoRepeatDelay", &QAbstractButton::autoRepeatDelay)
        .def("setAutoRepeatDelay", &QAbstractButton::setAutoRepeatDelay)
        .def("autoRepeatInterval", &QAbstractButton::autoRepeatInterval)
        .def("setAutoRepeatInterval", &QAbstractButton::setAutoRepeatInterval)
        //.def("group", &QAbstractButton::group)
        //.def("icon", &QAbstractButton::icon)
        //.def("iconSize", &QAbstractButton::iconSize)
        .def("isCheckable", &QAbstractButton::isCheckable)
        .def("isChecked", &QAbstractButton::isChecked)
        .def("isDown", &QAbstractButton::isDown)
        .def("setCheckable", &QAbstractButton::setCheckable)
        .def("setDown", &QAbstractButton::setDown)
        //.def("setIcon", &QAbstractButton::setIcon)
        //.def("setShortcut", &QAbstractButton::setShortcut)
        //.def("shortcut", &QAbstractButton::shortcut)
        .def("text", &QAbstractButton::text)
        .def("setText", &QAbstractButton::setText)
        .def("animateClick", [](QAbstractButton& self){ self.animateClick(); })
        .def("animateClick", &QAbstractButton::animateClick)
        .def("click", &QAbstractButton::click)
        .def("setChecked", &QAbstractButton::setChecked)
        //.def("setIconSize", QAbstractButton::setIconSize)
        .def("toggle", &QAbstractButton::toggle)
        .def_property_readonly(
            "clicked",
            [](QAbstractButton* self){ return ButtonClickSignal(self, &QAbstractButton::clicked); })
        .def_property_readonly(
            "toggled",
            [](QAbstractButton* self){ return ButtonBoolSignal(self, &QAbstractButton::toggled); })
        ;

    py::class_<QPushButton, PyQObjectHolder<QPushButton>, QAbstractButton>(m, "QPushButton")
        .def(py::init<QWidget*>(), py::arg("parent") = nullptr)
        .def(py::init<const QString&, QWidget*>(), py::arg("text"), py::arg("parent") = nullptr)
        .def("autoDefault", &QPushButton::autoDefault)
        .def("isDefault", &QPushButton::isDefault)
        .def("isFlat", &QPushButton::isFlat)
        .def("menu", &QPushButton::menu)
        .def("setAutoDefault", &QPushButton::setAutoDefault)
        .def("setDefault", &QPushButton::setDefault)
        .def("setFlat", &QPushButton::setFlat)
        .def("setMenu", &QPushButton::setMenu)
        .def("showMenu", &QPushButton::showMenu)
        ;
    
    py::class_<QToolButton, PyQObjectHolder<QToolButton>, QAbstractButton>(m, "QToolButton")
        .def("autoRaise", &QToolButton::autoRaise)
        ;

    py::class_<QCheckBox, PyQObjectHolder<QCheckBox>, QAbstractButton>(m, "QCheckBox")
        .def(py::init<>())
        .def(py::init<const QString&>())
        ;

    py::class_<QLabel, PyQObjectHolder<QLabel>, QWidget>(m, "QLabel")
        .def(py::init<>())
        .def(py::init<const QString&>())
        .def("setText", &QLabel::setText)
        ;

    py::class_<QAbstractSpinBox, PyQObjectHolder<QAbstractSpinBox>, QWidget>(m, "QAbstractSpinBox")
        .def("alignment", &QAbstractSpinBox::alignment)
        .def("setAlignment", &QAbstractSpinBox::setAlignment)
        ;

    py::class_<QSpinBox, PyQObjectHolder<QSpinBox>, QAbstractSpinBox> qSpinBox(m, "QSpinBox");

    typedef cnoid::QtSignal<void(QSpinBox::*)(int), void(int)> SpinBoxIntSignal;
    cnoid::PyQtSignal<SpinBoxIntSignal>(qSpinBox, "IntSignal");

    qSpinBox
        .def(py::init<>())
        .def("setMaximum", &QSpinBox::setMaximum)
        .def("setMinimum", &QSpinBox::setMinimum)
        .def("setRange", &QSpinBox::setRange)
        .def("maximum", &QSpinBox::maximum)
        .def("minimum", &QSpinBox::minimum)
        .def("setSingleStep", &QSpinBox::setSingleStep)
        .def("value", &QSpinBox::value)
        .def("setValue", &QSpinBox::setValue)
        .def_property_readonly(
            "valueChanged",
            [](QSpinBox* self){ return SpinBoxIntSignal(self, &QSpinBox::valueChanged); })
        ;

    py::class_<QDialog, PyQObjectHolder<QDialog>, QWidget> qDialog(m, "QDialog");

    typedef cnoid::QtSignal<void(QDialog::*)(), void()> DialogSignal;
    cnoid::PyQtSignal<DialogSignal>(qDialog, "Signal");
    typedef cnoid::QtSignal<void(QDialog::*)(int), void(int)> DialogIntSignal;
    cnoid::PyQtSignal<DialogIntSignal>(qDialog, "IntSignal");

    qDialog
        .def(py::init<>())
        .def("result", &QDialog::result)
        .def("setResult", &QDialog::setResult)
        .def("setModal", &QDialog::setModal)
        .def("accept", &QDialog::accept)
        .def("done", &QDialog::done)
        .def("exec", &QDialog::exec)
        .def("open", &QDialog::open)
        .def("reject", &QDialog::reject)
        .def_property_readonly(
            "accepted",
            [](QDialog* self){ return DialogSignal(self, &QDialog::accepted); })
        .def_property_readonly(
            "finished",
            [](QDialog* self){ return DialogIntSignal(self, &QDialog::finished); })
        .def_property_readonly(
            "rejected",
            [](QDialog* self){ return DialogSignal(self, &QDialog::rejected); })
        ;

    py::class_<QFrame, PyQObjectHolder<QFrame>, QWidget>(m, "QFrame");

    py::class_<QAbstractScrollArea, PyQObjectHolder<QAbstractScrollArea>, QFrame>(m, "QAbstractScrollArea")
        .def("horizontalScrollBarPolicy", &QAbstractScrollArea::horizontalScrollBarPolicy)
        .def("setHorizontalScrollBarPolicy", &QAbstractScrollArea::setHorizontalScrollBarPolicy)
        .def("verticalScrollBarPolicy", &QAbstractScrollArea::verticalScrollBarPolicy)
        .def("setVerticalScrollBarPolicy", &QAbstractScrollArea::setVerticalScrollBarPolicy)
        ;

    exportPyQtGuiLayoutClasses(m);
    exportPyQtGuiModelViewClasses(m);
}
