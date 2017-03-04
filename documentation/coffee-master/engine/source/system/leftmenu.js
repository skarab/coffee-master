function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6503\" class=\"headerLeftMenuInActive\"><a id=\"aID6503\" href=\"#\" OnMouseOver=\"link('_dir','system0',this)\" class=\"leftMenuLinkHeadInActive\">system</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Directories</div>\n");
document.write("<div id=\"divID6338\" class=\"leftMenuInActive\"><a id=\"aID6338\" href=\"#\" OnMouseOver=\"link('_dir','audio/audio0',this)\" class=\"leftMenuLinkInActive\">audio</a></div>\n");
document.write("<div id=\"divID6374\" class=\"leftMenuInActive\"><a id=\"aID6374\" href=\"#\" OnMouseOver=\"link('_dir','graphics/graphics0',this)\" class=\"leftMenuLinkInActive\">graphics</a></div>\n");
document.write("<div id=\"divID6390\" class=\"leftMenuInActive\"><a id=\"aID6390\" href=\"#\" OnMouseOver=\"link('_dir','input/input0',this)\" class=\"leftMenuLinkInActive\">input</a></div>\n");
document.write("<div id=\"divID6394\" class=\"leftMenuInActive\"><a id=\"aID6394\" href=\"#\" OnMouseOver=\"link('_dir','physics/physics0',this)\" class=\"leftMenuLinkInActive\">physics</a></div>\n");
document.write("<div id=\"divID6409\" class=\"leftMenuInActive\"><a id=\"aID6409\" href=\"#\" OnMouseOver=\"link('_dir','scene/scene0',this)\" class=\"leftMenuLinkInActive\">scene</a></div>\n");
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
