function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6512\" class=\"headerLeftMenuInActive\"><a id=\"aID6512\" href=\"#\" OnMouseOver=\"link('_dir','geometric0',this)\" class=\"leftMenuLinkHeadInActive\">geometric</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Directories</div>\n");
document.write("<div id=\"divID6273\" class=\"leftMenuInActive\"><a id=\"aID6273\" href=\"#\" OnMouseOver=\"link('_dir','box/box0',this)\" class=\"leftMenuLinkInActive\">box</a></div>\n");
document.write("<div id=\"divID6274\" class=\"leftMenuInActive\"><a id=\"aID6274\" href=\"#\" OnMouseOver=\"link('_dir','frustum/frustum0',this)\" class=\"leftMenuLinkInActive\">frustum</a></div>\n");
document.write("<div id=\"divID6275\" class=\"leftMenuInActive\"><a id=\"aID6275\" href=\"#\" OnMouseOver=\"link('_dir','line/line0',this)\" class=\"leftMenuLinkInActive\">line</a></div>\n");
document.write("<div id=\"divID6276\" class=\"leftMenuInActive\"><a id=\"aID6276\" href=\"#\" OnMouseOver=\"link('_dir','plane/plane0',this)\" class=\"leftMenuLinkInActive\">plane</a></div>\n");
document.write("<div id=\"divID6277\" class=\"leftMenuInActive\"><a id=\"aID6277\" href=\"#\" OnMouseOver=\"link('_dir','ray/ray0',this)\" class=\"leftMenuLinkInActive\">ray</a></div>\n");
document.write("<div id=\"divID6278\" class=\"leftMenuInActive\"><a id=\"aID6278\" href=\"#\" OnMouseOver=\"link('_dir','rectangle/rectangle0',this)\" class=\"leftMenuLinkInActive\">rectangle</a></div>\n");
document.write("<div id=\"divID6279\" class=\"leftMenuInActive\"><a id=\"aID6279\" href=\"#\" OnMouseOver=\"link('_dir','segment/segment0',this)\" class=\"leftMenuLinkInActive\">segment</a></div>\n");
document.write("<div id=\"divID6280\" class=\"leftMenuInActive\"><a id=\"aID6280\" href=\"#\" OnMouseOver=\"link('_dir','sphere/sphere0',this)\" class=\"leftMenuLinkInActive\">sphere</a></div>\n");
if(divID != "" && aID != "")
{
  var elemDiv = document.getElementById(divID);
  var elemA = document.getElementById(aID);
  if (elemDiv != undefined && elemA != undefined ) { // this is needed to abvoid crashing js on some memberpages 
    elemDiv.className = divClassName;
    elemA.className = aClassName;
  }
}
}
