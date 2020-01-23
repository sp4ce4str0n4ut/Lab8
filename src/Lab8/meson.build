myproject_src = files([
    'main.cpp'
])

python = dependency('python')
threads = dependency('threads')

executable(
    'Lab8',
    include_directories: src,
    sources: Lab8_src,
    dependencies: [python,threads],
    install: true,
)
