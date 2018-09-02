% number of symbols in simulation
Nsyms = 1e6;
% energy per symbol
Es = 1;
% energy per bit (2 bits/symbol for QPSK)
Eb = Es / 2;
% Eb/No values to simulate at, in dB
%EbNo_dB = 1:13;
EsNo_dB = 1:15;

% Eb/No values in linear scale
%EbNo_lin = 10.^(EbNo_dB / 10);
EsNo_lin = 10.^(EsNo_dB / 10);

% calculate theoretical bit error rate, functionally equivalent to:
EbNo_lin = EsNo_lin/2;
bit_err_theo = 0.5*erfc(sqrt(EbNo_lin));
figure;
bit_err = [118156988/902400008 93878403/902400008 71198673/902400008 50988080/902400008 33999806/902400008 20767165/902400008 11357509/902400008 5416650/902400008 2176534/902400008 706100/902400008 175424/902400008 30984/902400008 3588/902400008 240/902400008 7/902400008];
%semilogy(EbNo_dB, bit_err, 'b*', EbNo_dB, bit_err_theo, 'r', 'MarkerSize', 10, 'LineWidth', 2);
semilogy(EsNo_dB, bit_err, 'b*', EsNo_dB, bit_err_theo, 'r', 'MarkerSize', 10, 'LineWidth', 2);
%xlabel('Eb/No (dB)');
xlabel('Es/No (dB)');
ylabel('Bit error rate');
title('QPSK bit error rate');
legend('Simulation','Theory');
grid on;