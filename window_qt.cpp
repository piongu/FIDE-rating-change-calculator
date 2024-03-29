#include "window_qt.hpp"
#include <math.h> //to use fabs function
#include <cstdio> //to use sprintf function

float expected (int diff)
{
	int tab[43]={392,375,358,345,327,316,303,291,279,268,257,246,236,226,
		216,207,198,189,180,171,163,154,146,138,130,122,114,107,99,92,84,77,69,62,54,47,40,33,26,18,11,4,0};
        //values of rating difference intervals
        //curiously enough rating change is calculated according to table, not mathematical formula (which is only an approximation)
	int exp = 92;
	int i = 0;

	while(i<43 && fabs(diff) < tab[i])
	{
		i++;
		exp--;
	}

	if(diff>0)
		return exp/100.0;//100.0 in order to force returning float
	else
		return 1-exp/100.0;
}

void Window::calc()
{	
        //data collection
	int diff = 0;
	int k=0;
	float score = -1;
	float change = 0;
	if (outcome_radio[0]->isChecked()) score = 1;
	else if(outcome_radio[1]->isChecked()) score = 0.5;
	else score = 0;
	if (k_radio[0]->isChecked()) k = 10;
	else if(k_radio[1]->isChecked()) k = 15;
	else k = 30;

        //calculating rating change
	diff = (slider->value() - slider2->value());
	if(fabs(diff)>400)
	{
		if(slider->value() > slider2->value()) diff = 400;
		else diff = -400;
	}
	change = (score - expected(diff))*k;
	//std::cout<< "your change is:" << change << std::endl;
        //showing result in new window as a pushbutton
	char ch[512];
	sprintf(ch, "%.2f", change);
	QPushButton *result = new QPushButton(ch);
	QObject::connect(result, SIGNAL(clicked()), 
                        result, SLOT(close()));
	result->show();
}
Window::Window()
{
        setWindowTitle("rating change calculator (ELO system) by piongu - version 1.0");
	//enter ratings section
	spinBox = new QSpinBox(this);
	spinBox2 = new QSpinBox(this);
	slider = new QSlider(Qt::Horizontal);
	slider2 = new QSlider(Qt::Horizontal);
	calc_button = new QPushButton("calculate");
	exit_button = new QPushButton("quit");
	label = new QLabel("your rating:");
	label2 = new QLabel("opponent's rating:");
        source = new QLabel("source: https://github.com/piongu");
	//setting range of spinBoxes plus sliders
	spinBox->setRange(1000, 2900);
	slider->setRange(1000, 2900);
	spinBox2->setRange(1000, 2900);
	slider2->setRange(1000, 2900);

	//Connecting things
	QObject::connect(spinBox, SIGNAL(valueChanged(int)),
			slider, SLOT(setValue(int)));
	QObject::connect(slider, SIGNAL(valueChanged(int)),
			spinBox, SLOT(setValue(int)));
	spinBox->setValue(2000); //setting default value

	QObject::connect(spinBox2, SIGNAL(valueChanged(int)),
			slider2, SLOT(setValue(int)));
	QObject::connect(slider2, SIGNAL(valueChanged(int)),
			spinBox2, SLOT(setValue(int)));
	spinBox2->setValue(2000); //setting default value

	QObject::connect(calc_button, SIGNAL(clicked()), 
			this, SLOT(calc()));
	QObject::connect(exit_button, SIGNAL(clicked()),
			this,SLOT(close()));

	//adding two radio sections
	outcome_host = new QWidget;
	outcome_label = new QLabel("outcome:");
	outcome_radio[0] = new QRadioButton("victory", outcome_host);
	outcome_radio[1] = new QRadioButton("draw", outcome_host);
	outcome_radio[2] = new QRadioButton("defeat", outcome_host);
	outcome_radio[0]->setChecked(1); //first option as default

	k_host = new QWidget;
	k_label = new QLabel("your 'k':");
	k_radio[0] = new QRadioButton("10", k_host);
	k_radio[1] = new QRadioButton("15", k_host);
	k_radio[2] = new QRadioButton("30", k_host);
	k_radio[1]->setChecked(1); //middle option as default

	//Setting layouts
	main_layout = new QVBoxLayout;
	ratings_layout = new QHBoxLayout;
	radioslayout = new QHBoxLayout;
	outcome_layout = new QVBoxLayout;
	k_layout = new QVBoxLayout;

	k_layout->addWidget(k_label); //'k' section
	k_layout->addWidget(k_radio[0]);
	k_layout->addWidget(k_radio[1]);
	k_layout->addWidget(k_radio[2]);
	k_host->setLayout(k_layout);

	outcome_layout->addWidget(outcome_label); //outcome section
	outcome_layout->addWidget(outcome_radio[0]);
	outcome_layout->addWidget(outcome_radio[1]);
	outcome_layout->addWidget(outcome_radio[2]);
	outcome_host->setLayout(outcome_layout);

	radioslayout->addWidget(outcome_host);
	radioslayout->addWidget(k_host);

	ratings_layout->addWidget(label); //ratings section
	ratings_layout->addWidget(spinBox);
	ratings_layout->addWidget(slider);
	ratings_layout->addWidget(label2);
	ratings_layout->addWidget(spinBox2);
	ratings_layout->addWidget(slider2);

	main_layout->addLayout(ratings_layout); //main layout
	main_layout->addLayout(radioslayout);
	main_layout->addWidget(calc_button);
	main_layout->addWidget(exit_button);
        main_layout->addWidget(source);

	setLayout(main_layout);
	show();
}
Window::~Window() 
{
        //I leave this empty on purpose
        //according to my current knowledge in Qt allocated memory is freed when you close the window
        //in some way it's similiar to so called Garbage Collector used in Java language
}
