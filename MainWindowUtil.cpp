/* ========================================================================
   File:    MainWindowUtil.cpp
   Class:   Senior Design II Csc 59867
   Creator: Asad Kamal, Vincent Gong, RuLong Haung
   ======================================================================== */


#include "MainWindow.h"

void MainWindow::createGridLayout(QGridLayout* layout, int row, QString label, QSlider* slider,
                                  QDoubleSpinBox* spinBox, float lowerRange,  float upperRange, float initialVal)
{
    QLabel *spinnerLabel = new QLabel(label);

    slider->setValue(initialVal);
    slider->setRange(lowerRange, upperRange);

    spinBox->setValue(initialVal);
    spinBox->setRange(lowerRange, upperRange);

    layout->addWidget(spinnerLabel, row, 0);
    layout->addWidget(slider,       row, 1);
    layout->addWidget(spinBox,      row, 2);
}

void MainWindow::createGridLayout(QGridLayout* Layout, int Row, QString Label, QDoubleSpinBox* SpinBox,
                                                 QString unitLabel, float lowerRange,  float upperRange, float initialVal)
{
    QLabel *spinBoxLabel = new QLabel (Label);
    QLabel *unitBoxLabel = new QLabel (unitLabel);

    SpinBox->setValue(initialVal);
    SpinBox->setRange(lowerRange, upperRange);

    Layout->addWidget(spinBoxLabel, Row, 0);
    Layout->addWidget(SpinBox,      Row, 1);
    Layout->addWidget(unitBoxLabel, Row, 2);
}

void MainWindow::createGridLayout(QGridLayout* Layout, int Row, QString Label, QComboBox* comboBox,
                                                 QString unitLabel)
{
    QLabel *comboLabel = new QLabel (Label);
    QLabel *unitBoxLabel = new QLabel (unitLabel);

    comboBox->addItem("16 (Thick)");
    comboBox->addItem("18 (Medium)");
    comboBox->addItem("23 (Thin)");

    Layout->addWidget(comboLabel,    Row, 0);
    Layout->addWidget(comboBox,      Row, 1);
    Layout->addWidget(unitBoxLabel,  Row, 2);
}


void MainWindow::createGridLayout(QGridLayout* Layout, int Row, QString Labels, QString Label2)

{
    QLabel *labels = new QLabel (Labels);
    QLabel *dimenLabel = new QLabel (Label2);


    Layout->addWidget(labels,     Row, 0);
    Layout->addWidget(dimenLabel, Row, 1);
}

bool MainWindow::applyFilter(ImagePtr I1, ImagePtr I2)
{
	double brightness, contrast, gamma, filterSize, filterFctr;
    // error checking
    if(I1.isNull()) {
        IP_printfErr("applyFilter: Missing image");
        return 0;   // failure
    }

    brightness = m_brightness;
    gamma = m_gamma;
    filterSize = m_filterSize;
    filterFctr = m_filterFctr;

    if(m_contrast >= 0) {
    	contrast   = m_contrast / 25 + 1;
 	}
 	else {
 		contrast = 1 + (m_contrast/ 133);
 	}

    // apply filter
    IP_contrast(I1, brightness, contrast, 128, I2);
    IP_gammaCorrect(I2, gamma, I2);
    IP_sharpen(I2, filterSize, filterSize, filterFctr,I2);
    IP_copyImage(I2, m_imageDst);

    return 1;   // success
}

void MainWindow::display(int flag)
{
    // error checking
    if(m_imageSrc.isNull()) return;     // no input image
    if(m_imageDst.isNull())         // compute output image
        applyFilter(m_imageSrc, m_imageDst);

    // raise the appropriate widget from the stack
    m_stackWidget->setCurrentIndex(flag);

    // determine image to be displayed
    ImagePtr I;
    if(flag == 0)
        I = m_imageSrc;
    else    I = m_imageDst;

    // init dimensions of target
    int w = m_stackWidget->width();
    int h = m_stackWidget->height();

    // convert from ImagePtr to QImage to Pixmap
    QImage q;
    IP_IPtoQImage(I, q);
    QPixmap p = QPixmap::fromImage(q.scaled(QSize(w,h), Qt::KeepAspectRatio));

    // assign pixmap to label widget for display
    QLabel *widget = (QLabel *) m_stackWidget->currentWidget();
    widget->setPixmap(p);
}

void MainWindow::preview()
{
    applyFilter(m_imageSrc, m_imageDst);

    // display requested image
    int i;
    for(i=0; i<2; i++)
        if(m_radioButton[i]->isChecked()) break;

    switch(i) {
    case 0: displayIn   (); break;
    case 1: displayOut  (); break;
    }
}
