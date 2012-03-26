/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2012.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#ifndef _FWDATATOOLS_PATIENT_HPP_
#define _FWDATATOOLS_PATIENT_HPP_

#include <fwCore/base.hpp>

#include <fwTools/Type.hpp>

#include <fwData/PatientDB.hpp>
#include <fwData/Patient.hpp>
#include <fwData/Study.hpp>
#include <fwData/Acquisition.hpp>
#include <fwData/Reconstruction.hpp>

#include "fwDataTools/export.hpp"

namespace fwDataTools
{


/**
 * @brief   This class contains helper to generate and compare patients.
 * @class   Patient.
 * @author  IRCAD (Research and Development Team).
 * @date    2012.
 *
 */
class Patient : public ::fwCore::BaseObject
{

public :

    fwCoreClassDefinitionsWithFactoryMacro((Patient)( ::fwCore::BaseObject ),
                                           (()),
                                           new Patient
                                          );
    fwCoreAllowSharedFromThis();

    /**
     * @brief Removed specified patient in PatientDB.
     * @param patientDB    PatientDB containing specified Patient to remove
     * @param patient      patient to remove
     */
    FWDATATOOLS_API static void removePatient(::fwData::PatientDB::sptr patientDB,
                                                ::fwData::Patient::sptr patient);

    /**
     * @brief Removed specified study in Patient.
     * @param patient    Patient containing specified Study to remove
     * @param study      study to remove
     */
    FWDATATOOLS_API static void removeStudy(::fwData::Patient::sptr patient,
                                               ::fwData::Study::sptr study);

    /**
     * @brief Removed specified acquisition in Study.
     * @param study    Study containing specified acquisition to remove
     * @param acq      acquisition to remove
     */
    FWDATATOOLS_API static void removeAcquisition(::fwData::Study::sptr study,
                                                  ::fwData::Acquisition::sptr acq);

    /**
     * @brief Generate a patient.
     * @param patient           patient to generate
     * @param nbStudy           number of study to add in patient
     * @param nbAcquisition     number of acquisition to add in patient
     * @param nbReconstruction  number of reconstruction to add in patient
     */
    FWDATATOOLS_API static void generatePatient(::fwData::Patient::sptr patient,
                                                const unsigned char nbStudy,
                                                const unsigned char nbAcquisition,
                                                const unsigned char nbReconstruction);

    /**
     * @brief compare two patients.
     * @return true if the patients are equal.
     * @note if false, the patients differences are written in SLM log
     */
    FWDATATOOLS_API static bool comparePatient(::fwData::Patient::sptr patient1, ::fwData::Patient::sptr patient2);


    /**
     * @brief Generate a study.
     * @param study             study to generate
     * @param nbAcquisition     number of acquisition to add in study
     * @param nbReconstruction  number of reconstruction to add in study
     */
    FWDATATOOLS_API static void generateStudy(::fwData::Study::sptr study,
                                              const unsigned char nbAcquisition,
                                              const unsigned char nbReconstruction);

    /**
     * @brief compare two studies.
     * @return true if the studies are equal.
     * @note if false, the studies differences are written in SLM log
     */
    FWDATATOOLS_API static bool compareStudy(::fwData::Study::sptr study1, ::fwData::Study::sptr study2);

    /**
     * @brief Generate an acquisition.
     * @param acq               acquisition to generate
     * @param nbReconstruction  number of reconstruction to add in acquisition
     */
    FWDATATOOLS_API static void generateAcquisition(::fwData::Acquisition::sptr acq,
                                                    const unsigned char nbReconstruction);

    /**
     * @brief compare two acquisitions.
     * @return true if the acquisition are equal.
     * @note if false, the acquisition differences are written in SLM log
     */
    FWDATATOOLS_API static bool compareAcquisition(::fwData::Acquisition::sptr acq1, ::fwData::Acquisition::sptr acq2);

    /**
     * @brief Generate a reconstruction.
     * @param rec   reconstruction to generate
     */
    FWDATATOOLS_API static void generateReconstruction(::fwData::Reconstruction::sptr rec);

    /**
     * @brief compare two reconstructions.
     * @return true if the reconstructions are equal.
     * @note if false, the reconstructions differences are written in SLM log
     */
    FWDATATOOLS_API static bool compareReconstruction(::fwData::Reconstruction::sptr rec1, ::fwData::Reconstruction::sptr rec2);

    /**
     * @brief Generate a mesh.
     * @param mesh mesh to generate
     */
    FWDATATOOLS_API static void generateMesh( ::fwData::Mesh::sptr mesh );

    /**
     * @brief compare two meshes.
     * @return true if meshes are equal.
     * @note if false, mesh differences are written in SLM log
     */
    FWDATATOOLS_API static bool compareMesh( ::fwData::Mesh::sptr mesh1, ::fwData::Mesh::sptr mesh2, std::string errorPrefix = "" );

    /**
     * @brief compare two data array meshes.
     * @return true if data array meshes are equal.
     * @note if false, data array meshe differences are written in SLM log
     */
    FWDATATOOLS_API static bool compareDataArrayMesh( ::fwData::Mesh::sptr mesh1, ::fwData::Mesh::sptr mesh2 );

    /**
     * @brief compare two materials.
     * @return true if materials are equal.
     * @note if false, material differences are written in SLM log
     */
    FWDATATOOLS_API static bool compareMaterial( ::fwData::Material::sptr mat1, ::fwData::Material::sptr mat2, std::string errorPrefix ="" );

    /**
     * @brief compare two colors.
     * @return true if colors are equal.
     * @note if false, color differences are written in SLM log
     */
    FWDATATOOLS_API static bool compareColor( ::fwData::Color::sptr col1, ::fwData::Color::sptr col2, float colorTolerance = 1.f/255.f, std::string errorPrefix = "" );

protected:


    //! @brief Constructor.
    FWDATATOOLS_API Patient();

    //! @brief Destructor.
    FWDATATOOLS_API virtual ~Patient();

};

} // namespace fwDataTools

#endif // _FWDATATOOLS_PATIENT_HPP_