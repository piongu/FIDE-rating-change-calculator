#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <iostream>
#include <QApplication>
#include <QHBoxLayout>
#include <QSlider>
#include <QSpinBox>
#include <QPushButton>
#include <QLabel>
#include <QRadioButton>

class Window : public QWidget
{
    Q_OBJECT;

  public slots:
    void calc(); //this function calculates ELO change

  private:
	QVBoxLayout *main_layout;
	QHBoxLayout *ratings_layout; //to keep enter ratings section
	//Label plus SpinBox & Slider to enter rating of a player
        QSpinBox *spinBox;
	QSlider *slider;
	QLabel *label;
	//Label plus SpinBox & Slider to enter opponent's rating
	QSpinBox *spinBox2;
	QSlider *slider2;
	QLabel *label2;
	//PushButtons to calculate Elo change or to exit the program
	QPushButton *calc_button;
	QPushButton *exit_button;
	
	//RadioButtons' section with label in one layout to choose result and 'k'
	QHBoxLayout *radioslayout; //one layout to keep two radios sections
	QVBoxLayout *outcome_layout;
	QRadioButton *outcome_radio[3];
	QLabel *outcome_label;
	QWidget *outcome_host;
	QVBoxLayout *k_layout;
	QRadioButton *k_radio[3];
	QLabel *k_label;
	QWidget *k_host;
    
  public:
    Window();
    ~Window();
};

#endif 
