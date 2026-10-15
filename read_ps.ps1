$port = New-Object System.IO.Ports.SerialPort "COM7", 115200
$port.ReadTimeout = 1000
try {
    $port.Open()
    $port.DtrEnable = $true
    $port.RtsEnable = $true
    Start-Sleep -Milliseconds 800
    $data = $port.ReadExisting()
    Write-Output "SERIAL:"
    Write-Output $data
    $port.Close()
} catch {
    Write-Output "ERROR: $($_.Exception.Message)"
}
