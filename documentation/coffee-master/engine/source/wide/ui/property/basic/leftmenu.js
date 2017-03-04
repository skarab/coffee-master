function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6435\" class=\"headerLeftMenuInActive\"><a id=\"aID6435\" href=\"#\" OnMouseOver=\"link('_dir','basic0',this)\" class=\"leftMenuLinkHeadInActive\">basic</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Directories</div>\n");
document.write("<div id=\"divID6434\" class=\"leftMenuInActive\"><a id=\"aID6434\" href=\"#\" OnMouseOver=\"link('_dir','text/text0',this)\" class=\"leftMenuLinkInActive\">text</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID970\" class=\"leftMenuInActive\"><a id=\"aID970\" href=\"#\" OnMouseOver=\"link('_class','PropertyBase49249',this)\" class=\"leftMenuLinkInActive\">PropertyBase</a></div>\n");
document.write("<div id=\"divID971\" class=\"leftMenuInActive\"><a id=\"aID971\" href=\"#\" OnMouseOver=\"link('_class','PropertyColor49249',this)\" class=\"leftMenuLinkInActive\">PropertyColor</a></div>\n");
document.write("<div id=\"divID972\" class=\"leftMenuInActive\"><a id=\"aID972\" href=\"#\" OnMouseOver=\"link('_class','PropertyEuler49249',this)\" class=\"leftMenuLinkInActive\">PropertyEuler</a></div>\n");
document.write("<div id=\"divID973\" class=\"leftMenuInActive\"><a id=\"aID973\" href=\"#\" OnMouseOver=\"link('_class','PropertyImage49249',this)\" class=\"leftMenuLinkInActive\">PropertyImage</a></div>\n");
document.write("<div id=\"divID974\" class=\"leftMenuInActive\"><a id=\"aID974\" href=\"#\" OnMouseOver=\"link('_class','PropertyQuaternion49249',this)\" class=\"leftMenuLinkInActive\">PropertyQuaternion</a></div>\n");
document.write("<div id=\"divID975\" class=\"leftMenuInActive\"><a id=\"aID975\" href=\"#\" OnMouseOver=\"link('_class','PropertyVector349249',this)\" class=\"leftMenuLinkInActive\">PropertyVector3</a></div>\n");
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
