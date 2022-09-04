$Path=$args[0]
Write-Output "Compiling shaders..."
Get-ChildItem "Shaders" | ForEach-Object {
    Write-Output "Compiling shader: "$_.FullName
    $newFile = $_.BaseName+"-"+$_.Extension.Replace('.','')+".spv"
    C:/VulkanSDK/1.3.224.1/Bin/glslc.exe $_.FullName -o $pwd/Resources/Shaders/$newFile
}
Write-Output "Compiled shaders successfully"
Write-Output "Moving shaders to $Path"
robocopy "$pwd/Resources"  *.* "$pwd../cmake-build-debug/StartEngine/resources" /S
Write-Output "Moving shaders to %path% successfully"
exit 0