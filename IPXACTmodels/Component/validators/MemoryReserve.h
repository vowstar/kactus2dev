//-----------------------------------------------------------------------------
// File: MemoryReserve.h
//-----------------------------------------------------------------------------
// Project: Kactus 2
// Author: Mikko Teuho
// Date: 26.11.2015
//
// Description:
// Class for determining overlapping within an area.
//-----------------------------------------------------------------------------

#ifndef MEMORYRESERVE_H
#define MEMORYRESERVE_H

#include <IPXACTmodels/ipxactmodels_global.h>

#include <QSharedPointer>
#include <QString>
#include <QVector>

//-----------------------------------------------------------------------------
//! Class for determining overlapping within an area.
//-----------------------------------------------------------------------------
class IPXACTMODELS_EXPORT MemoryReserve
{
public:

	/*!
	 *  The constructor.
	 */
    MemoryReserve();

    //! The destructor.
    ~MemoryReserve();

    /*!
     *  Reserve an area.
     *
     *      @param [in] newId       Id of the reserved area.
     *      @param [in] newBegin    Start point of the area.
     *      @param [in] newEnd      End point of the area.
     */
    void addArea(QString const& newId, int newBegin, int newEnd);
    
    /*!
     *  Check if reserved areas overlap.
     *
     *      @return True, if overlap exists, otherwise false.
     */
    bool hasOverlap();

    /*!
     *  Find errors related to overlapping.
     *
     *      @param [in] errors          The error list.
     *      @param [in] itemIdentifier  Identifier for the overlapping items.
     *      @param [in] context         Context used to help find the error.
     */
    void findErrorsInOverlap(QVector<QString>& errors, QString const& itemIdentifier, QString const& context);

private:

	// Disable copying.
	MemoryReserve(MemoryReserve const& rhs);
	MemoryReserve& operator=(MemoryReserve const& rhs);

    //-----------------------------------------------------------------------------
    // Data.
    //-----------------------------------------------------------------------------

    // A memory area.
    struct MemoryArea
    {
        //! Identifier for the area.
        QString id_;

        //! Start point of the area.
        int begin_;

        //! End point of the area.
        int end_;

        /*!
         *  Assignment operator for MemoryArea.
         *
         *      @param [in] other   Memory area to be assigned.
         *
         *      @return The newly assigned memory area.
         */
        MemoryArea& operator=(const MemoryArea& other);
        
        /*!
         *  Check if a memory area has lower start point than another memory area.
         *
         *      @param [in] other   Memory area being compared to.
         */
        bool operator<(const MemoryArea& other) const;
    };

    //! The currently reserved memory areas.
    QVector<MemoryArea> reservedArea_;
};

#endif // MEMORYRESERVE_H
