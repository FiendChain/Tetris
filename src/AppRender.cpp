#include "App.hpp"
#include <SFML/Graphics.hpp>

void App::Render()
{
    // centre panel
    m_CentrePanel.clear(sf::Color(0, 0, 0, 120));
    m_CurrentTetrimino->Draw(&m_CentrePanel);
    m_Blocks.Draw(&m_CentrePanel);
    m_CentrePanel.display();

    // right panel
    m_RightPanel.clear(sf::Color::Transparent);
    for (auto& block: m_FutureTetriminos)
    {
        if (block) block->Draw(&m_RightPanel);
    }
    m_RightPanel.display();

    // left panel
    m_LeftPanel.clear(sf::Color::Transparent);
    if (m_StoredTetrimino) m_StoredTetrimino->Draw(&m_LeftPanel);
    m_LeftPanel.display();

    // window
    m_Window.clear(sf::Color::White);
    RenderPanel(m_LeftPanel, sf::Vector2f(0, 0));
    static int centrePanelPosX = m_LeftPanel.getSize().x;
    RenderPanel(m_CentrePanel, sf::Vector2f(centrePanelPosX, 0));
    static int rightPanelPosX = centrePanelPosX + m_CentrePanel.getSize().x;
    RenderPanel(m_RightPanel, sf::Vector2f(rightPanelPosX, 0));

    m_Window.display();
}

void App::RenderPanel(const sf::RenderTexture& panel, const sf::Vector2f& position)
{
    sf::Sprite panelSprite(panel.getTexture());
    panelSprite.setPosition(position);
    m_Window.draw(panelSprite);
}
