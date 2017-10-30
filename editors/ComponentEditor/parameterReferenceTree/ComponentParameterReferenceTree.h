//-----------------------------------------------------------------------------
// File: ComponentParameterReferenceTree.h
//-----------------------------------------------------------------------------
// Project: Kactus2
// Author: Mikko Teuho
// Date: 28.09.2018
//
// Description:
// Tree widget for displaying references to a parameter within a component.
//-----------------------------------------------------------------------------

#ifndef COMPONENTPARAMETERREFERENCETREE_H
#define COMPONENTPARAMETERREFERENCETREE_H

#include <editors/ComponentEditor/common/ExpressionFormatter.h>
#include <editors/ComponentEditor/parameterReferenceTree/ParameterReferenceTree.h>

#include <QSharedPointer>

class Component;
class ModuleParameter;
class FileSet;
class FileBuilder;
class File;
class BuildCommand;
class AddressSpace;
class Segment;
class ComponentInstantiation;
class DesignConfigurationInstantiation;
class DesignInstantiation;
class Port;
class MemoryMapBase;
class MemoryMap;
class MemoryRemap;
class AddressBlock;
class RegisterBase;
class Register;
class Field;
class BusInterface;
class MirroredSlaveInterface;
class MasterInterface;
class RemapState;
class RemapPort;
class ComponentParameterReferenceCounter;

//-----------------------------------------------------------------------------
//! Tree widget for displaying references to a parameter within a component.
//-----------------------------------------------------------------------------
class ComponentParameterReferenceTree : public ParameterReferenceTree
{
    Q_OBJECT
public:

    /*!
     *   The constructor.
     *
     *      @param [in] component               The component whose references to display.
     *      @param [in] expressionFormatter     Formatter for expressions.
     *      @param [in] referenceCounter        Calculator for parameter references.
     *      @param [in] parent                  The parent widget.
     */
    ComponentParameterReferenceTree(QSharedPointer<Component> component,
        QSharedPointer<ExpressionFormatter> expressionFormatter,
        QSharedPointer<ComponentParameterReferenceCounter> referenceCounter, QWidget *parent = 0);

	/*!
     *  The destructor.
     */
    ~ComponentParameterReferenceTree();

    /*!
     *  Set a new component.
     *
     *      @param [in] newComponent    The selected component.
     */
    void setComponent(QSharedPointer<Component> newComponent);

private:
    
	// Disable copying.
    ComponentParameterReferenceTree(ComponentParameterReferenceTree const& rhs);
    ComponentParameterReferenceTree& operator=(ComponentParameterReferenceTree const& rhs);

    /*!
     *  Setup the reference tree.
     */
    void setupTree();

    /*!
     *  Get the parameter reference calculator.
     */
    QSharedPointer<ParameterReferenceCounter> getReferenceCounter() const;

    /*!
     *  Create references for file sets.
     */
    void createReferencesForFileSets();

    /*!
     *  Create references for file builders.
     *
     *      @param [in] fileBuilders    The selected file builders.
     *      @param [in] parentItem      The parent item of the file builders item.
     */
    void createReferencesForFileBuilders(QSharedPointer<QList<QSharedPointer<FileBuilder> > > fileBuilders,
        QTreeWidgetItem* parentItem);

    /*!
     *  Create references for a single file builder.
     *
     *      @param [in] fileBuilder     The selected file builder.
     *      @param [in] parentItem      The parent item.
     */
    void createReferencesForSingleFileBuilder(QSharedPointer<FileBuilder> fileBuilder, QTreeWidgetItem* parentItem);

    /*!
     *  Create references from the selected files.
     *
     *      @param [in] fileList    A list of files with possible references.
     *      @param [in] parentItem  The parent item.
     */
    void createReferencesForFiles(QSharedPointer<QList<QSharedPointer<File> > > fileList,
        QTreeWidgetItem* parentItem);

    /*!
     *  Create references for a single file.
     *
     *      @param [in] selectedFile    The selected file.
     *      @param [in] parentItem      The parent item.
     */
    void createReferencesForSingleFile(QSharedPointer<File> selectedFile, QTreeWidgetItem* parentItem);

    /*!
     *  Create the references for model parameters.
     *
     *      @param [in] parameters  The model parameters to create references for.
     *      @param [in] parentItem  The parent item for references.
     */
    void createReferencesForModuleParameters(QSharedPointer<QList<QSharedPointer<ModuleParameter> > > parameters,
        QTreeWidgetItem* parentItem);

    /*!
     *  Create references for instantiations.
     */
    void createReferencesForInstantiations();

    /*!
     *  Create references for component instantiations.
     *
     *      @param [in] topInstantiationsItem   The parent tree item.
     */
    void createReferencesForComponentInstantiations(QTreeWidgetItem* topInstantiationsItem);

    /*!
     *  Create references for design configuration instantiations.
     *
     *      @param [in] topInstantiationsItem   The parent tree item.
     */
    void createReferencesForDesignConfigurationInstantiations(QTreeWidgetItem* topInstantiationsItem);

    /*!
     *  Create references for design instantiations.
     *
     *      @param [in] topInstantiationsItem   The parent tree item.
     */
    void createReferencesForDesignInstantiations(QTreeWidgetItem* topInstantiationsItem);

    /*!
     *  Create the references for ports.
     */
    void createReferencesForPorts();

    /*!
     *  Create the references for address spaces.
     */
    void createReferencesForAddressSpaces();

    /*!
     *  Create the references for a single address space.
     *
     *      @param [in] addressSpace    The address space to create references for.
     *      @param [in] parent          The parent tree item of the new address space item.
     */
    void createItemsForAddressSpace(QSharedPointer<AddressSpace> addressSpace, QTreeWidgetItem* parent);
    
    /*!
     *  Create the references for segments within an address space.
     *
     *      @param [in] addressSpace    The address space to create references for.
     *      @param [in] parent          The parent tree item of the new segment items.
     */
    void createReferencesForSegments(QSharedPointer<AddressSpace> addressSpace, QTreeWidgetItem* parent);
        
    /*!
     *  Create the references a segment within an address space.
     *
     *      @param [in] segment    The segment to create references for.
     *      @param [in] parent     The parent tree item of the segment items.
     */
    void createItemsForSegment(QSharedPointer<Segment> segment, QTreeWidgetItem* parent);

    /*!
     *  Create the references for memory maps.
     */
    void createReferencesForMemoryMaps();

    /*!
     *  Create the references for a single abstract memory map.
     *
     *      @param [in] memoryMap           The memory map / memory remap.
     *      @param [in] topMemoryMapItem    The parent tree item of the new memory map tree item.
     */
    void createReferencesForSingleMemoryMap(QSharedPointer<MemoryMapBase> memoryMap,
        QTreeWidgetItem* memoryRemapItem);

    /*!
     *  Create the references for a single address block.
     *
     *      @param [in] addressBlock                The address block.
     *      @param [in] middleAddressBlocksItem     The parent tree item of the new address block tree item.
     */
    void createReferencesForSingleAddressBlock(QSharedPointer<AddressBlock> addressBlock,
        QTreeWidgetItem* middleAddressBlocksItem);

    /*!
     *  Create the references for a single register.
     *
     *      @param [in] targetRegister  The register.
     *      @param [in] parentItem      The parent tree item of the new register tree item.
     */
    void createReferencesForSingleRegister(QSharedPointer<Register> targetRegister, QTreeWidgetItem* parentItem);

    /*!
     *  Create references for bus interfaces.
     */
    void createReferencesForBusInterfaces();

    /*!
     *  Create references for remap states.
     */
    void createReferencesForRemapStates();

    /*!
     *  Create tree items for a port that is referencing this parameter.
     *
     *      @param [in] port        The referencing port.
     *      @param [in] parent      The parent of the upcoming item.
     */
    void createItemsForPort(QSharedPointer<Port> port, QTreeWidgetItem* parent);

    /*!
     *  Create tree items for an address block that is referencing this parameter.
     *
     *      @param [in] targetAddressBlock  The referencing address block.
     *      @param [in] parent              The parent for the upcoming item.
     */
    void createItemsForAddressBlock(QSharedPointer<AddressBlock> targetAddressBlock, QTreeWidgetItem* parent);

    /*!
     *  Create tree items for a register that is referencing this parameter.
     *
     *      @param [in] targetRegister  The referencing register.
     *      @param [in] parent          The parent of the upcoming item.
     */
    void createItemsForRegister(QSharedPointer<Register> targetRegister, QTreeWidgetItem* parent);

    /*!
     *  Create tree items for a register field that is referencing this parameter.
     *
     *      @param [in] targetField     The referencing register field.
     *      @param [in] parent          The parent of the new item.
     */
    void createItemsForField(QSharedPointer<Field> targetField, QTreeWidgetItem* parent);

    //-----------------------------------------------------------------------------
    // Data.
    //-----------------------------------------------------------------------------

    //! The component in which this id is situated.
    QSharedPointer<Component> component_;

    //! Reference calculator for component parameters.
    QSharedPointer<ComponentParameterReferenceCounter> referenceCounter_;
};

#endif // COMPONENTPARAMETERREFERENCETREE_H
