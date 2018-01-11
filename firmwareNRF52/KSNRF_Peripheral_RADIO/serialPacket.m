clear;

s = kSerial(115200, 'clear');
s.setRecordBufferSize(1024 * 16);
s.setRecvThreshold(0);
s.open();

t_idx = 1: 2;
for i = 1 : 10000
    [packetData, packetInfo, packetLens] = s.packetRecv();
    if ~isempty(packetLens) && packetLens > 0

        tims = s.ks.data(t_idx, :);
        tt   = s.getTime(t_idx, 0, 0.01);
        freq = s.getFreq(t_idx, 100, 0.01);
        
%         freq = s.getFreq(1);
%         rmag = s.ks.data(1: 3, :);

        fprintf('[%06i][%02i]', s.ks.lens, packetLens);
        fprintf('[%02i:%02i:%02i] ', tt(1), tt(2), fix(tt(3) / 10));
        fprintf('[%4.0fHz] ', freq);
%         fprintf('rmag[%6i, %6i, %6i]', rmag(:, end));
        fprintf('\n');
    end
end
s.close();

% {
% check packet
[rate, lost, dt] = s.getLostRate(t_idx, freq, 0.001);
if lost == 0
    fprintf('---- [%05.2f%%] No packet loss ( %i / %i ) ----\n', rate * 100, lost, s.ks.lens);
else
    fprintf('---- [%05.2f%%] Packet loss ( %i / %i ) ----\n', rate * 100, lost, s.ks.lens);
end
% plot(1 : s.ks.lens - 1, dt)
%}
%{
s.save2mat('log/rawData', {'tims(1:2)'});
%}
