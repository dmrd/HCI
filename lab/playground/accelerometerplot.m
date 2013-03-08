figure(1)
clf
hold on

for i = 1:3
    h = plot(time, data(:, i));
    i
    high = max(data(:, i));
    low = min(data(:, i));
    (high - low) / 135
    hline = plot(time, ones(length(time), 1) * high);
    lline = plot(time, ones(length(time), 1) * low);
    if i == 1
        set(h, 'Color', [1 0 0])
        set(hline, 'Color', [1 0 0], 'LineStyle', '--')
        set(lline, 'Color', [1 0 0], 'LineStyle', '--')        
    elseif i == 2
        set(h, 'Color', [0 1 0])
        set(hline, 'Color', [0 1 0], 'LineStyle', '--')
        set(lline, 'Color', [0 1 0], 'LineStyle', '--')
    else
        set(h, 'Color', [0 0 1])
        set(hline, 'Color', [0 0 1], 'LineStyle', '--')
        set(lline, 'Color', [0 0 1], 'LineStyle', '--')
    end
end

xlabel('Time (s)', 'FontSize', 20)
ylabel('Accelerometer values', 'FontSize', 20)
set(gca, 'FontSize', 14)

figure(2)
clf
hold on

for i = 1:3
    h = plot(-90:45:90, tilt(:, i));
    if i == 1
        set(h, 'Color', [1 0 0])
    elseif i == 2
        set(h, 'Color', [0 1 0])
    else
        set(h, 'Color', [0 0 1])
    end
end