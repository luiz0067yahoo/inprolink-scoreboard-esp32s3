$port = New-Object System.IO.Ports.SerialPort "COM6", 115200
$port.ReadTimeout = 1000
try {
    $port.Open()
    $port.DtrEnable = $false
    $port.RtsEnable = $false
    Start-Sleep -Milliseconds 1500
    $data = $port.ReadExisting()
    Write-Output "SERIAL:"
    Write-Output $data
    $port.Close()
} catch {
    Write-Output "ERROR: $($_.Exception.Message)"
}
