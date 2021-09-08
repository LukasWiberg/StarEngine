$Path=$args[0]
echo "Compiling shaders..."
C:/VulkanSDK/1.2.176.1/Bin/glslc.exe $pwd/Shaders/a.vert -o $pwd/Resources/Shaders/a-vert.spv
C:/VulkanSDK/1.2.176.1/Bin/glslc.exe $pwd/Shaders/a.frag -o $pwd/Resources/Shaders/a-frag.spv
echo "Compiled shaders successfully"
echo "Moving shaders to $Path"
robocopy "$pwd/Resources"  *.* "$Path" /S
echo "Moving shaders to %path% successfully"
exit 0