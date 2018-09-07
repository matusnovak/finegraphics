module.exports = {
    base: '/finegraphics',
    title: "FineGraphics",
    description: "A simple OpenGL helper library part of a FineFramework project",
    themeConfig: {
        sidebar: 'auto',
        nav: [
            { text: 'Home', link: '/' },
            { text: 'Install', link: '/INSTALL' },
            { text: 'Examples', link: '/examples/' },
            { text: 'Modules', link: '/doxygen/modules' },
            {
                text: 'Classes',
                items: [
                    { text: 'Class List', link: '/doxygen/annotated' },
                    { text: 'Class Index', link: '/doxygen/classes' },
                    { text: 'Function Index', link: '/doxygen/functions' },
                    { text: 'Variable Index', link: '/doxygen/variables' },
                    { text: 'Enumeration Index', link: '/doxygen/enumerations' }
                ]
            },
            { text: 'Files', link: '/doxygen/files' },
            { text: 'Pages', link: '/doxygen/pages' }
        ]
    }
}
