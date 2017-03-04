function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6348\" class=\"headerLeftMenuInActive\"><a id=\"aID6348\" href=\"#\" OnMouseOver=\"link('_dir','light0',this)\" class=\"leftMenuLinkHeadInActive\">light</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Directories</div>\n");
document.write("<div id=\"divID6347\" class=\"leftMenuInActive\"><a id=\"aID6347\" href=\"#\" OnMouseOver=\"link('_dir','directional/directional0',this)\" class=\"leftMenuLinkInActive\">directional</a></div>\n");
document.write("<div id=\"divID6349\" class=\"leftMenuInActive\"><a id=\"aID6349\" href=\"#\" OnMouseOver=\"link('_dir','ies/ies0',this)\" class=\"leftMenuLinkInActive\">ies</a></div>\n");
document.write("<div id=\"divID6350\" class=\"leftMenuInActive\"><a id=\"aID6350\" href=\"#\" OnMouseOver=\"link('_dir','point/point0',this)\" class=\"leftMenuLinkInActive\">point</a></div>\n");
document.write("<div id=\"divID6351\" class=\"leftMenuInActive\"><a id=\"aID6351\" href=\"#\" OnMouseOver=\"link('_dir','spot/spot0',this)\" class=\"leftMenuLinkInActive\">spot</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID850\" class=\"leftMenuInActive\"><a id=\"aID850\" href=\"#\" OnMouseOver=\"link('_class','ComponentLight54809',this)\" class=\"leftMenuLinkInActive\">ComponentLight</a></div>\n");
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
