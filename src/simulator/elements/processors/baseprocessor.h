/***************************************************************************
 *   Copyright (C) 2012 by Santiago González                               *
 *   santigoro@gmail.com                                                   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, see <http://www.gnu.org/licenses/>.  *
 *                                                                         *
 ***************************************************************************/

#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "terminalwidget.h"


class MAINMODULE_EXPORT BaseProcessor : public QObject
{
    Q_OBJECT
    public:
        BaseProcessor( QObject* parent=0 );
        ~BaseProcessor();
        
 static BaseProcessor* self() { return m_pSelf; }
 
        QString getFileName();

        virtual void    setDevice( QString device );
        virtual QString getDevice();
        
        virtual void setDataFile( QString datafile );

        virtual bool loadFirmware( QString file )=0;
        virtual bool getLoadStatus() { return m_loadStatus; }
        virtual void terminate();

        virtual void setSteps( double steps );
        virtual void step()=0;
        virtual void stepOne()=0;
        virtual void stepCpu()=0;
        virtual void reset()=0;
        virtual int  pc()=0;
        
        virtual void hardReset( bool reset );
        virtual int getRamValue( QString name );
        virtual int getRamValue( int address )=0;
        virtual int getRegAddress( QString name );
        virtual void addWatchVar( QString name, int address, QString type );
        virtual void updateRamValue( QString name );
        
        virtual void setUsart( bool usart ) { m_usartTerm = usart; }
        virtual void setSerPort( bool serport ) { m_serialPort = serport; }
        virtual void uartOut( uint32_t value );
        virtual void uartIn( uint32_t value );
        
        virtual void initialized();
        virtual QStringList getRegList() { return m_regList; }
        
        virtual void setRegisters();
    
    protected:
 static BaseProcessor* m_pSelf;
        
        virtual int  validate( int address )=0;
        
        void runSimuStep();

        QString m_symbolFile;
        QString m_dataFile;
        QString m_device;
        
        double m_mcuStepsPT;
        int  m_msimStep;
        double m_nextCycle;

        QStringList m_regList;
        QHash<QString, int> m_regsTable;     // int max 32 bits
        QHash<QString, QString> m_typeTable;

        bool m_resetStatus;
        bool m_loadStatus;
        bool m_usartTerm;
        bool m_serialPort;
};


#endif

