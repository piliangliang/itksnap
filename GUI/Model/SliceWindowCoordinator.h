/*=========================================================================

  Program:   ITK-SNAP
  Module:    $RCSfile: SliceWindowCoordinator.h,v $
  Language:  C++
  Date:      $Date: 2009/05/04 20:15:57 $
  Version:   $Revision: 1.5 $
  Copyright (c) 2007 Paul A. Yushkevich
  
  This file is part of ITK-SNAP 

  ITK-SNAP is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
 
  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.

  -----

  Copyright (c) 2003 Insight Software Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.  See the above copyright notices for more information. 

=========================================================================*/
#ifndef __SliceWindowCoordinator_h_
#define __SliceWindowCoordinator_h_

#include "GenericSliceModel.h"
#include <itkObject.h>
#include <SNAPEvents.h>
#include "PropertyModel.h"

class SliceWindowCoordinator;

/*
  Who fires the events? Widgets interacting with the Zoom Factor model expect
  events from the model. We don't want the parent object to fire events
  separately. But this means, everyone should interact with the model, not
  directly with the slice window coordinator.

  */

/**
 * \class SliceWindowCoordinator
 * \brief Coordinates the zoom (and perhaps other) aspects of behavior between
 * three orthogonal slice windows.
 *
 * Helps manage linked zoom (the concept that 1 mm in image space is always the
 * same number of pixels in each slice view).
 */
class SliceWindowCoordinator : public AbstractModel
{
public:

  irisITKObjectMacro(SliceWindowCoordinator, itk::Object)

  FIRES(LinkedZoomUpdateEvent)

  /** Assigns three windows for the coordinator to manage */
  void RegisterSliceModels(GenericSliceModel *windows[3]);

  /** Specify whether the coordinator should maintain linked zoom
   * in the three slice windows */
  void SetLinkedZoom(bool flag);

  /** Specify whether the coordinator should maintain linked zoom
   * in the three slice windows */
  irisGetMacro(LinkedZoom,bool)
  
  /** Set the zoom to a fraction of the optimal zoom.  This makes 
   * the most sense when the zoom level is linked, but can be performed 
   * regardless */
  void SetZoomFactorAllWindows(float factor);

  /** Set the zoom to an absolute value in all windows */
  void SetZoomLevelAllWindows(float level);

  /**
    This sets the zoom 'percentage'. For example, if x=1, the zoom is set
    such that one screen pixel is matched to the smallest of voxel dims. If
    x=2, two pixels match the smallest voxel dim, and so on. The idea is that
    if your image is isotropic, by setting x=1,2,4, etc., you can avoid
    aliasing the displayed image
    */
  void SetZoomPercentageInAllWindows(float x);

  /** Reset the zoom in all windows to an optimal value, ie, such a zoom
   * that the image fits into each of the windows.  Depending on whether 
   * the zoom is linked or not, this will either zoom each slice as much
   * as possible, or zoom the largest of the 3 slices as much as possible */
  void ResetViewToFitInAllWindows();

  /** Reset the zoom in one window to optimal value.  When linked zoom is
   * maintained, this has the same effect as ResetViewToFitInAllWindows, 
   * and if not, it only affects the given window */
  void ResetViewToFitInOneWindow(unsigned int window);

  /** When one of the windows wants to change the zoom w.r.t. a user
   * action, this class will adjust, if necessary, the zoom in the other
   * windows */
  void OnZoomUpdateInWindow(unsigned int window, float zoom);

  /** React to a resizing of the windows.  This will try to maintain the current view
   * depending on the state.  If the zooms are in 'reset' state, this will keep
   * them in the reset state, and otherwise, it will maintain the zoom levels */
  void OnWindowResize();

  /** Get the common zoom factor */
  float GetCommonZoomLevel();

  /** Get the zoom factor that will fit all three slices optimally */
  float GetCommonOptimalFitZoomLevel();

  /** Get the model representing the optimal zoom */
  irisGetMacro(CommonZoomFactorModel, AbstractRangedDoubleProperty*)

  /** Constrain a zoom factor to reasonable limits */
  float ClampZoom(unsigned int window,float zoom);

  /** Get the range of zoom allowed */
  void GetZoomRange(unsigned int window, float &minZoom, float &maxZoom);

  /** Get the window number n */
  GenericSliceModel *GetSliceModel(unsigned int window)
    { return m_SliceModel[window]; }


protected:

  /** Constructor */
  SliceWindowCoordinator();

  /** Virtual destructor */
  virtual ~SliceWindowCoordinator();

  /** Pointer to the application driver for this UI object */
  //IRISApplication *m_Driver;

  /** Pointer to the global state object (shorthand) */
  //GlobalState *m_GlobalState;

  /** Pointer to GUI that contains this Window3D object */
  //UserInterfaceBase *m_ParentUI;   

  /** The image data object that is displayed in this window */
  //GenericImageData *m_ImageData;

  /** The pointers to three window interactors managed by this class */
  GenericSliceModel *m_SliceModel[3];

  /** Whether or not linked zoom is maintained */
  bool m_LinkedZoom;

  /** Whether the windows have been registered */
  bool m_WindowsRegistered;

  /** Method that sets all the zooms to a common value */
  void SetCommonZoomToSmallestWindowZoom();

  /** Compute the smallest of the optimal zoom levels of the slice views */
  double ComputeSmallestOptimalZoomLevel();

  // Chold model governing linked zoom properties
  SmartPtr<AbstractRangedDoubleProperty> m_CommonZoomFactorModel;

  // Access method for getting common zoom value and range
  bool GetCommonZoomValueAndRange(double &zoom,
                                  NumericValueRange<double> *range);
  void SetCommonZoomValue(double zoom);
};

#endif // __SliceWindowCoordinator_h_