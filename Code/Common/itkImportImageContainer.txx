/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkImportImageContainer.txx
  Language:  C++
  Date:      $Date$
  Version:   $Revision$

  Copyright (c) Insight Software Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

  Portions of this code are covered under the VTK copyright.
  See VTKCopyright.txt or http://www.kitware.com/VTKCopyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef __itkImportImageContainer_txx
#define __itkImportImageContainer_txx

#include "itkImportImageContainer.h"
#include <cstring>

namespace itk
{

template <typename TElementIdentifier, typename TElement>
ImportImageContainer<TElementIdentifier , TElement>
::ImportImageContainer()
{
  m_ImportPointer = 0;
  m_ContainerManageMemory = true;
  m_Capacity = 0;
  m_Size = 0;
}


template <typename TElementIdentifier, typename TElement>
ImportImageContainer< TElementIdentifier , TElement >
::~ImportImageContainer()
{
  DeallocateElements(m_ImportPointer);
}


/**
 * Tell the container to allocate enough memory to allow at least
 * as many elements as the size given to be stored.  
 */
template <typename TElementIdentifier, typename TElement>
void
ImportImageContainer< TElementIdentifier , TElement >
::Reserve(ElementIdentifier size)
{
  // Reserve has a Resize semantics. We keep it that way for
  // backwards compatibility .
  // See http://www.itk.org/Bug/view.php?id=2893 for details
  if (m_ImportPointer)
    {
    if (size > m_Capacity)
      {
      TElement* temp = this->AllocateElements(size);
      // only copy the portion of the data used in the old buffer
      memcpy(temp, m_ImportPointer, m_Size*sizeof(TElement));
      
      DeallocateElements(m_ImportPointer);
      
      m_ImportPointer = temp;
      m_ContainerManageMemory = true;
      m_Capacity = size;
      m_Size = size;
      this->Modified();
      }
    else
      {
      m_Size = size;
      this->Modified();
      }
    }
  else
    {
    m_ImportPointer = this->AllocateElements(size);
    m_Capacity = size;
    m_Size = size;
    m_ContainerManageMemory = true;
    this->Modified();
    }
}


/**
 * Tell the container to try to minimize its memory usage for storage of
 * the current number of elements.  
 */
template <typename TElementIdentifier, typename TElement>
void
ImportImageContainer< TElementIdentifier , TElement >
::Squeeze(void)
{
  if (m_ImportPointer)
    {
    if (m_Size < m_Capacity)
      {
      TElement* temp = this->AllocateElements(m_Size);
      memcpy(temp, m_ImportPointer, m_Size*sizeof(TElement));

      DeallocateElements(m_ImportPointer);
      
      m_ImportPointer = temp;
      m_ContainerManageMemory = true;
      m_Capacity = m_Size;

      this->Modified();
      }
    }
}


/**
 * Tell the container to try to minimize its memory usage for storage of
 * the current number of elements.  
 */
template <typename TElementIdentifier, typename TElement>
void
ImportImageContainer< TElementIdentifier , TElement >
::Initialize(void)
{
  if (m_ImportPointer)
    {
    DeallocateElements(m_ImportPointer);
    
    m_ImportPointer = 0;
    m_ContainerManageMemory = true;
    m_Capacity = 0;
    m_Size = 0;
    
    this->Modified();
    }
}


/**
 * Set the pointer from which the image data is imported.  "num" is
 * the number of pixels in the block of memory. If
 * "LetContainerManageMemory" is false, then the application retains
 * the responsibility of freeing the memory for this image data.  If
 * "LetContainerManageMemory" is true, then this class will free the
 * memory when this object is destroyed.
 */
template <typename TElementIdentifier, typename TElement>
void
ImportImageContainer< TElementIdentifier , TElement >
::SetImportPointer(TElement *ptr, TElementIdentifier num,
                   bool LetContainerManageMemory)
{
  DeallocateElements(m_ImportPointer);
  m_ImportPointer = ptr;
  m_ContainerManageMemory = LetContainerManageMemory;
  m_Capacity = num;
  m_Size = num;

  this->Modified();
}

template <typename TElementIdentifier, typename TElement>
TElement* ImportImageContainer< TElementIdentifier , TElement >
::AllocateElements(ElementIdentifier size) const
{
  // Encapsulate all image memory allocation here to throw an
  // exception when memory allocation fails even when the compiler
  // does not do this by default.
  TElement* data;
  try
    {
    data = new TElement[size];
    }
  catch(...)
    {
    data = 0;
    }
  if(!data)
    {
    // We cannot construct an error string here because we may be out
    // of memory.  Do not use the exception macro.
    throw MemoryAllocationError(__FILE__, __LINE__,
                                "Failed to allocate memory for image.",
                                ITK_LOCATION);
    }
  return data;
}

template <typename TElementIdentifier, typename TElement>
void ImportImageContainer< TElementIdentifier , TElement >
::DeallocateElements(const TElement* ptr) const
{
  // Encapsulate all image memory deallocation here
  if (ptr && m_ContainerManageMemory)
    {
    // A const_cast seems necessary for some compilers (e.g. MSVC)
    // that do not support deleting const pointers
    delete [] const_cast<TElement*>(ptr);
    }
}

template <typename TElementIdentifier, typename TElement>
void
ImportImageContainer< TElementIdentifier , TElement >
::PrintSelf(std::ostream& os, Indent indent) const
{
  Superclass::PrintSelf(os,indent);

  os << indent << "Pointer: " << static_cast<void *>(m_ImportPointer) << std::endl;
  os << indent << "Container manages memory: "
     << (m_ContainerManageMemory ? "true" : "false") << std::endl;
  os << indent << "Size: " << m_Size << std::endl;
  os << indent << "Capacity: " << m_Capacity << std::endl;
}

} // end namespace itk

#endif
