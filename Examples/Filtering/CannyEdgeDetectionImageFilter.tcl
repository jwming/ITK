#
#  Example on the use of the CannyEdgeDetection filter
#
package require InsightToolkit

set reader [ itkImageFileReaderF2_New ]
set writer [ itkImageFileWriterUS2_New ]

set outputCast [ itkRescaleIntensityImageFilterF2US2_New ]

set filter [ itkCannyEdgeDetectionImageFilterF2F2_New ]

$filter     SetInput [ $reader     GetOutput ]
$outputCast SetInput [ $filter     GetOutput ]
$writer     SetInput [ $outputCast GetOutput ]


$reader SetFileName [lindex $argv 0]
$writer SetFileName [lindex $argv 1]


$outputCast SetOutputMinimum       0
$outputCast SetOutputMaximum   65535

set variance   [expr [lindex $argv 2]]
set threshold  [expr [lindex $argv 3]]


$filter SetVariance     $variance
$filter SetThreshold    $threshold


$writer Update


exit

