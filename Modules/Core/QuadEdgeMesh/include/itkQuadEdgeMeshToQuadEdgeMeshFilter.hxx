/*=========================================================================
 *
 *  Copyright Insight Software Consortium
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/
#ifndef __itkQuadEdgeMeshToQuadEdgeMeshFilter_hxx
#define __itkQuadEdgeMeshToQuadEdgeMeshFilter_hxx

#include "itkQuadEdgeMeshToQuadEdgeMeshFilter.h"

namespace itk
{
// ---------------------------------------------------------------------
template< class TInputMesh, class TOutputMesh >
QuadEdgeMeshToQuadEdgeMeshFilter< TInputMesh, TOutputMesh >
::QuadEdgeMeshToQuadEdgeMeshFilter()
{
  this->Superclass::SetNumberOfRequiredInputs(1);
  this->Superclass::SetNumberOfRequiredOutputs(1);

  this->Superclass::SetNthOutput( 0, OutputMeshType::New() );
}

// ---------------------------------------------------------------------
template< class TInputMesh, class TOutputMesh >
void
QuadEdgeMeshToQuadEdgeMeshFilter< TInputMesh, TOutputMesh >
::CopyMeshToMesh(const TInputMesh *in, TOutputMesh *out)
{
  CopyMeshToMeshPoints(in, out);
  CopyMeshToMeshEdgeCells(in, out);
  CopyMeshToMeshCells(in, out);
  CopyMeshToMeshPointData(in, out);
  CopyMeshToMeshCellData(in, out);
}

// ---------------------------------------------------------------------
template< class TInputMesh, class TOutputMesh >
void
QuadEdgeMeshToQuadEdgeMeshFilter< TInputMesh, TOutputMesh >
::CopyInputMeshToOutputMesh()
{
  this->CopyInputMeshToOutputMeshGeometry();
  this->CopyInputMeshToOutputMeshFieldData();
}

// ---------------------------------------------------------------------
template< class TInputMesh, class TOutputMesh >
void
QuadEdgeMeshToQuadEdgeMeshFilter< TInputMesh, TOutputMesh >
::CopyInputMeshToOutputMeshGeometry()
{
  this->CopyInputMeshToOutputMeshPoints();
  this->CopyInputMeshToOutputMeshEdgeCells();
  this->CopyInputMeshToOutputMeshCells();
}

// ---------------------------------------------------------------------
template< class TInputMesh, class TOutputMesh >
void
QuadEdgeMeshToQuadEdgeMeshFilter< TInputMesh, TOutputMesh >
::CopyInputMeshToOutputMeshFieldData()
{
  this->CopyInputMeshToOutputMeshPointData();
  this->CopyInputMeshToOutputMeshCellData();
}

// ---------------------------------------------------------------------
template< class TInputMesh, class TOutputMesh >
void
QuadEdgeMeshToQuadEdgeMeshFilter< TInputMesh, TOutputMesh >
::CopyInputMeshToOutputMeshPoints()
{
  const InputMeshType *in = this->GetInput();
  OutputMeshType *     out = this->GetOutput();

  CopyMeshToMeshPoints(in, out);
}

// ---------------------------------------------------------------------
template< class TInputMesh, class TOutputMesh >
void
QuadEdgeMeshToQuadEdgeMeshFilter< TInputMesh, TOutputMesh >
::CopyInputMeshToOutputMeshEdgeCells()
{
  const InputMeshType *in = this->GetInput();
  OutputMeshType *     out = this->GetOutput();

  CopyMeshToMeshEdgeCells(in, out);
}

// ---------------------------------------------------------------------
template< class TInputMesh, class TOutputMesh >
void
QuadEdgeMeshToQuadEdgeMeshFilter< TInputMesh, TOutputMesh >
::CopyInputMeshToOutputMeshCells()
{
  const InputMeshType *in = this->GetInput();
  OutputMeshType *     out = this->GetOutput();

  CopyMeshToMeshCells(in, out);
}

// ---------------------------------------------------------------------
template< class TInputMesh, class TOutputMesh >
void
QuadEdgeMeshToQuadEdgeMeshFilter< TInputMesh, TOutputMesh >
::CopyInputMeshToOutputMeshPointData()
{
  const InputMeshType *in = this->GetInput();
  OutputMeshType *     out = this->GetOutput();

  CopyMeshToMeshPointData(in, out);
}

// ---------------------------------------------------------------------
template< class TInputMesh, class TOutputMesh >
void
QuadEdgeMeshToQuadEdgeMeshFilter< TInputMesh, TOutputMesh >
::CopyInputMeshToOutputMeshCellData()
{
  const InputMeshType *in = this->GetInput();
  OutputMeshType *     out = this->GetOutput();

  CopyMeshToMeshCellData(in, out);
}
} // end namespace itk

#endif