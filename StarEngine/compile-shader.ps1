$Path=$args[0]
echo "Compiling shaders..."
Get-ChildItem "Shaders" | ForEach-Object {
    echo "Compiling shader: "+$_.FullName
    $newFile = $_.BaseName+"-"+$_.Extension.Replace('.','')+".spv"
    C:/VulkanSDK/1.2.176.1/Bin/glslc.exe $_.FullName -o $pwd/Resources/Shaders/$newFile
}
echo "Compiled shaders successfully"
echo "Moving shaders to $Path"
robocopy "$pwd/Resources"  *.* "$Path" /S
echo "Moving shaders to %path% successfully"
exit 0