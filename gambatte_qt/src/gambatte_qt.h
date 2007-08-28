/***************************************************************************
 *   Copyright (C) 2007 by Sindre Aam�s                                    *
 *   aamas@stud.ntnu.no                                                    *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License version 2 as     *
 *   published by the Free Software Foundation.                            *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License version 2 for more details.                *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   version 2 along with this program; if not, write to the               *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/


#ifndef GAMBATTE_QT_H
#define GAMBATTE_QT_H

#include <QList>
#include <QMainWindow>
#include <QSize>
#include <vector>
#include <gambatte.h>
#include "videobufferreseter.h"
#include "samplescalculator.h"

class QAction;
class QMenu;
// class QTextEdit;
class AudioEngine;
class BlitterWidget;
class VideoDialog;
class InputDialog;
class FullResToggler;
class BlitterContainer;

class InputGetter : public InputStateGetter {
public:
	InputState is;
	const InputState& operator()() { return is; }
};

class GambatteQt : public QMainWindow {
	Q_OBJECT

public:
	GambatteQt(int argc, const char *const argv[]);
	~GambatteQt();

protected:
	void timerEvent(QTimerEvent *event);
	void keyPressEvent(QKeyEvent *e);
	void keyReleaseEvent(QKeyEvent *e);
	void closeEvent(QCloseEvent *e);
// 	void showEvent(QShowEvent *event);

private slots:
	void open();
	void openRecentFile();
	void about();
	void resetWindowSize();
	void toggleFullScreen();
	void toggleMenuHidden();
// 	void gl();
// 	void xv();
	void videoSettingsChange();
	void execVideoDialog();
	void execInputDialog();

private:
	void createActions();
	void createMenus();
	void loadFile(const QString &fileName);
	AudioEngine* initAudio();
	void run();
	void stop();
	void pause();
	void unpause();
	void setSamplesPrFrame();
// 	void calculateSamples(unsigned bufPos, unsigned bufSize);
	void setCurrentFile(const QString &fileName);
	void updateRecentFileActions();
	QString strippedName(const QString &fullFileName);
// 	void toggleFullScreen();
// 	void pauseAudio();
	void execDialog(QDialog *dialog);

	Gambatte gambatte;
// 	QString curFile;
//	QSize fixedSize;

	std::vector<AudioEngine*> audioEngines;
	std::vector<BlitterWidget*> blitters;
	
	InputGetter inputGetter;
	VideoBufferReseter resetVideoBuffer;
	
	int16_t *sndBuffer;

	BlitterContainer *blitterContainer;
	QAction *exitAct;
	QAction *separatorAct;
	QAction *fsAct;
	QAction *hideMenuAct;
	InputDialog *inputDialog;
	VideoDialog* videoDialog;
	BlitterWidget *blitter;
	FullResToggler *fullResToggler;

	enum { MaxRecentFiles = 8 };
	QAction *recentFileActs[MaxRecentFiles];
	
	AudioEngine *ae;
	
	unsigned sampleRate;
	unsigned samplesPrFrame;
	
	int timerId;
	
	SamplesCalculator samplesCalc;

	bool running;
	bool turbo;
	//bool esc;
};

#endif
