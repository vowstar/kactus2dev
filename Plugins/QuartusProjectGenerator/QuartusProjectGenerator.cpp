//-----------------------------------------------------------------------------
// File: QuartusProjectGenerator.cpp
//-----------------------------------------------------------------------------
// Project: Kactus 2
// Author: Mikko Teuho
// Date: 02.06.2015
//
// Description:
// The plugin for generating quartus projects containing quartus project files and quartus settings files.
//-----------------------------------------------------------------------------

#include "QuartusProjectGenerator.h"
#include "QuartusGenerator.h"

#include <library/LibraryInterface.h>

#include <Plugins/PluginSystem/IPluginUtility.h>

#include <IPXACTmodels/Design/Design.h>

#include <IPXACTmodels/designConfiguration/DesignConfiguration.h>

#include <IPXACTmodels/Component/Component.h>
#include <IPXACTmodels/kactusExtensions/KactusAttribute.h>

#include <IPXACTmodels/common/VLNV.h>

#include <QtPlugin>
#include <QDebug>
#include <QFileDialog>
#include <IPXACTmodels/Component/View.h>
#include "IPXACTmodels/Component/DesignConfigurationInstantiation.h"
#include "IPXACTmodels/Component/DesignInstantiation.h"

//-----------------------------------------------------------------------------
// Function: QuartusProjectGenerator::QuartusProjectGenerator()
//-----------------------------------------------------------------------------
QuartusProjectGenerator::QuartusProjectGenerator(): utility_(nullptr)
{

}

//-----------------------------------------------------------------------------
// Function: QuartusProjectGenerator::getName()
//-----------------------------------------------------------------------------
QString QuartusProjectGenerator::getName() const
{
	static QString name(tr("Quartus Project Generator"));
	return name;
}

//-----------------------------------------------------------------------------
// Function: QuartusProjectGenerator::getVersion()
//-----------------------------------------------------------------------------
QString QuartusProjectGenerator::getVersion() const
{
    static QString version(tr("1.1"));
    return version;
}

//-----------------------------------------------------------------------------
// Function: QuartusProjectGenerator::getDescription()
//-----------------------------------------------------------------------------
QString QuartusProjectGenerator::getDescription() const
{
    static QString description(tr("Generates quartus project file and quartus settings file for a HW design."));
    return description;
}

//-----------------------------------------------------------------------------
// Function: QuartusProjectGenerator::getVendor()
//-----------------------------------------------------------------------------
QString QuartusProjectGenerator::getVendor() const
{
    static QString vendor(tr("TUT"));
    return vendor;
}

//-----------------------------------------------------------------------------
// Function: QuartusProjectGenerator::getLicence()
//-----------------------------------------------------------------------------
QString QuartusProjectGenerator::getLicence() const
{
    static QString licence(tr("GPL2"));
    return licence;
}

//-----------------------------------------------------------------------------
// Function: QuartusProjectGenerator::getLicenceHolder()
//-----------------------------------------------------------------------------
QString QuartusProjectGenerator::getLicenceHolder() const
{
    static QString holder(tr("Public"));
    return holder;
}

//-----------------------------------------------------------------------------
// Function: MemoryMapHeaderGenerator::getSettingsWidget()
//-----------------------------------------------------------------------------
QWidget* QuartusProjectGenerator::getSettingsWidget()
{
    return nullptr;
}

//-----------------------------------------------------------------------------
// Function: MemoryMapHeaderGenerator::getIcon()
//-----------------------------------------------------------------------------
QIcon QuartusProjectGenerator::getIcon() const
{
    return QIcon(QStringLiteral(":icons/quartus_generator.png"));
}

//-----------------------------------------------------------------------------
// Function: QuartusProjectGenerator::checkGeneratorSupport()
//-----------------------------------------------------------------------------
bool QuartusProjectGenerator::checkGeneratorSupport(QSharedPointer<Component const> component,
    QSharedPointer<Design const> design,
    QSharedPointer<DesignConfiguration const> designConfiguration) const
{
    if (component && component->getImplementation() == KactusAttribute::HW)
    {
        if ((designConfiguration && designConfiguration->getDesignConfigImplementation() == KactusAttribute::HW) ||
            (design && design->getDesignImplementation() == KactusAttribute::HW))
        {
            return true;
        }
    }

    return false;
}

//-----------------------------------------------------------------------------
// Function: QuartusProjectGenerator::runGenerator()
//-----------------------------------------------------------------------------
void QuartusProjectGenerator::runGenerator(IPluginUtility* utility, 
    QSharedPointer<Component> component,
    QSharedPointer<Design> design,
    QSharedPointer<DesignConfiguration> designConfiguration)
{
    utility->printInfo(tr("Running %1 %2.").arg(getName(), getVersion()));

    utility_ = utility;

    QString path = QFileDialog::getExistingDirectory(utility->getParentWidget(),
        tr("Set the directory for the Quartus project"),
        utility->getLibraryInterface()->getPath(component->getVlnv()));

	if (path.isEmpty())
	{
		utility->printInfo(tr("Generation aborted: No path given."));
		return;
	}

	QSharedPointer<View> openView = getOpenView(component, designConfiguration, design);

	QuartusGenerator quartusGenerator(utility);

	connect(&quartusGenerator, SIGNAL(errorMessage(QString const&)),
		this, SLOT(onErrorMessage(QString const&)), Qt::UniqueConnection);
	connect(&quartusGenerator, SIGNAL(noticeMessage(QString const&)),
		this, SLOT(onNoticeMessage(QString const&)), Qt::UniqueConnection);

	QString generatorInformation = getName() + QLatin1Char(' ') + getVersion();

	quartusGenerator.readExistingPinMap(component);
	quartusGenerator.parseFiles(component, openView);
	quartusGenerator.generateProject(path, component->getVlnv().getName(), generatorInformation);

	utility->printInfo(tr("Quartus project generation complete."));
}

//-----------------------------------------------------------------------------
// Function: QuartusProjectGenerator::getProgramRequirements()
//-----------------------------------------------------------------------------
QList<IPlugin::ExternalProgramRequirement> QuartusProjectGenerator::getProgramRequirements()
{
    return QList<IPlugin::ExternalProgramRequirement>();
}

//-----------------------------------------------------------------------------
// Function: QuartusProjectGenerator::onErrorMessage()
//-----------------------------------------------------------------------------
void QuartusProjectGenerator::onErrorMessage(QString const& message)
{
    utility_->printError(message);
}

//-----------------------------------------------------------------------------
// Function: QuartusProjectGenerator::onNoticeMessage()
//-----------------------------------------------------------------------------
void QuartusProjectGenerator::onNoticeMessage(QString const& message)
{
    utility_->printInfo(message);
}

//-----------------------------------------------------------------------------
// Function: QuartusProjectGenerator::getOpenView()
//-----------------------------------------------------------------------------
QSharedPointer<View> QuartusProjectGenerator::getOpenView(QSharedPointer<Component> component,
	QSharedPointer<DesignConfiguration> desConf, QSharedPointer<Design> design)
{
    foreach (QSharedPointer<View> currentView, *component->getViews())
    {
		if ( desConf )
		{
			foreach ( QSharedPointer<DesignConfigurationInstantiation> insta,
				*component->getDesignConfigurationInstantiations() )
			{
				if ( (*insta->getDesignConfigurationReference()) == desConf->getVlnv()
					&& currentView->getDesignConfigurationInstantiationRef() == insta->name() )
				{
					return currentView;
				}
			}
		}

		if ( design )
		{
			foreach (QSharedPointer<DesignInstantiation> insta, *component->getDesignInstantiations() )
			{
				if ( (*insta->getDesignReference()) == design->getVlnv()
					&& currentView->getDesignInstantiationRef() == insta->name() )
				{
					return currentView;
				}
			}
		}
    }

    return QSharedPointer<View>();
}
